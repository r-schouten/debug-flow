#include "filteredconsole.h"

FilteredConsole::FilteredConsole()
{
    nodeSettings = new FilteredNodeSettings();
    console = new QPlainTextEdit(this);
    console->setReadOnly(true);
    console->document()->setMaximumBlockCount(1000);


    layout = new QVBoxLayout(this);
    verticalLayout = new QHBoxLayout(this);

    layout->addLayout(verticalLayout);
    layout->addWidget(console);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    console->setPalette(p);

    contextFilter = new ContextFilter(nodeSettings);
    //connect(contextFilter, SIGNAL(propertyChanged(Property*)),this,SLOT(propertyChanged(Property*)));

}

FilteredConsole::~FilteredConsole()
{
    while(items.size() > 0)
    {
        delete items.takeAt(0);
    }
    while(properyBoxes.size() > 0)
    {
        delete properyBoxes.takeAt(0);
    }
    delete contextFilter;
}
//void FilteredConsole::propertyChanged(Property* property)
//{

//    if(property->itemModel == nullptr)
//    {
//        QComboBox* newBox = new QComboBox;
//        property->itemModel = new QStandardItemModel();
//        newBox->setModel(property->itemModel);
//        verticalLayout->addWidget(newBox);
//        properyBoxes.append(property->itemModel);
//    }

//    QListIterator<PropertyOption*> iterator(property->options);
//    while(iterator.hasNext())
//    {
//        PropertyOption* option = iterator.next();
//        if(option->standardItem == nullptr)
//        {
//            option->standardItem = new QStandardItem();

//            connect(property->itemModel, SIGNAL(itemChanged(QStandardItem*)),
//                    &option->mapper, SLOT(map()));

//            option->mapper.setMapping(property->itemModel, option);
//            connect(&option->mapper, SIGNAL(mapped(QObject*)),
//                    this, SLOT(slot_changed(QObject*)));

//            option->standardItem->setText(option->name);
//            option->standardItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
//            option->standardItem->setData(Qt::Checked, Qt::CheckStateRole);

//            property->itemModel->appendRow(option->standardItem);
//        }
//    }

//}
//void FilteredConsole::slot_changed(QObject* propertyOption)
//{
//    PropertyOption* option = dynamic_cast<PropertyOption*>(propertyOption);
//    if(!option)return;

//    option->setEnabled(option->standardItem->checkState());
//}

void FilteredConsole::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = contextFilter->filterData(&result, source->bufferReader, &currentCharFormat);

    //qDebug("result: %s",destination.toStdString().c_str());
    //qDebug() << source->bufferReader->availableSize();
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
