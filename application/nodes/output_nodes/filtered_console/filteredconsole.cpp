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


    QListIterator<Tag*> tagIterator(nodeSettings->tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        TagComboBox* newTagComboBox = new TagComboBox(currentTag);
        tagComboBoxes.append(newTagComboBox);
        newTagComboBox->loadTag();
        verticalLayout->addWidget(newTagComboBox);
    }
    connect(nodeSettings, SIGNAL(optionAdded(Tag*,TagOption*)),this,SLOT(optionAdded(Tag*,TagOption*)));

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


void FilteredConsole::optionAdded(Tag *destinationTag, TagOption *option)
{
    qDebug("[debug,FilteredConsolePropertiesWidget::optionAdded]");

    TagComboBox* destinationComboBox = nullptr;
    if(tagComboBoxes.size() <= destinationTag->tagIndex)
    {
        destinationComboBox = new TagComboBox(destinationTag);
        tagComboBoxes.append(destinationComboBox);
        verticalLayout->addWidget(destinationComboBox);
    }
    else {
        destinationComboBox = tagComboBoxes.at(destinationTag->tagIndex);
    }

    TagOptionItem* item = new TagOptionItem(option);
    item->setText(option->name);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(item->tagOption->enabled? Qt::Checked:Qt::Unchecked, Qt::CheckStateRole);

    destinationComboBox->itemModel->appendRow(item);
}

void FilteredConsole::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = contextFilter->filterData(&result, source->bufferReader, &currentCharFormat);


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
