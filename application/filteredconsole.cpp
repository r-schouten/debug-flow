#include "filteredconsole.h"

FilteredConsole::FilteredConsole(QWidget *parent)
    :parent(parent)
{
    if(dynamic_cast<InputNode*>(this))
    {
        hasInput = true;
    }
    if(dynamic_cast<OutputNode*>(this))
    {
        hasOutput = true;
    }

    console = new QPlainTextEdit(parent);
    console->setReadOnly(true);
    console->document()->setMaximumBlockCount(1000);


    layout = new QVBoxLayout(parent);
    verticalLayout = new QHBoxLayout(parent);

    layout->addLayout(verticalLayout);
    layout->addWidget(console);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    console->setPalette(p);

    tagFilter = new TagFilter();
    connect(tagFilter, SIGNAL(propertyChanged(Property*)),this,SLOT(propertyChanged(Property*)));

}
void FilteredConsole::propertyChanged(Property* property)
{
    qDebug() << "propery changed";

    if(property->itemModel == nullptr)
    {
        QComboBox* newBox = new QComboBox;
        property->itemModel = new QStandardItemModel();
        newBox->setModel(property->itemModel);
        verticalLayout->addWidget(newBox);
        properyBoxes.append(property->itemModel);
    }

    QListIterator<PropertyOption*> iterator(property->options);
    while(iterator.hasNext())
    {
        PropertyOption* option = iterator.next();
        if(option->standardItem == nullptr)
        {
            option->standardItem = new QStandardItem();

//            connect(property->itemModel, SIGNAL(itemChanged(QStandardItem*)),
//                    &option->mapper, SLOT(map()));

//            option->mapper.setMapping(property->itemModel, option);
//            connect(&option->mapper, SIGNAL(mapped(QObject*)),
//                    this, SLOT(slot_changed(QObject*)));

            option->standardItem->setText(option->name);
            option->standardItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            option->standardItem->setData(Qt::Checked, Qt::CheckStateRole);

            property->itemModel->appendRow(option->standardItem);
        }
    }

}
void FilteredConsole::slot_changed(QObject* propertyOption)
{
    PropertyOption* option = dynamic_cast<PropertyOption*>(propertyOption);
    if(!option)return;
    qDebug("slot changed");

    option->setEnabled(option->standardItem->checkState());
}

void FilteredConsole::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = tagFilter->filterData(&result, source->bufferReader, &currentCharFormat);

    //qDebug("result: %s",destination.toStdString().c_str());
    //qDebug() << result;
    console->moveCursor(QTextCursor::End);
    console->setCurrentCharFormat(oldFormat);
    console->insertPlainText(result);
    console->moveCursor(QTextCursor::End);

    if(styleChanged)
    {
        //when ansi is found the filter stops searching and is perhaps not empty, read it again
        NotifyBufferUpdate(source);
    }
}

void FilteredConsole::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Backspace:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            break;
        }
}

void FilteredConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    console->setFocus();
}

void FilteredConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void FilteredConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
void FilteredConsole::clear()
{
    console->clear();
}
