#include "filteredconsole.h"

FilteredConsole::FilteredConsole()
{
    nodeSettings = new FilteredNodeSettings();
    console = new QPlainTextEdit(this);
    console->setReadOnly(true);
    loadMaxLines();

    layout = new QVBoxLayout(this);
    verticalLayout = new QHBoxLayout(this);

    layout->addLayout(verticalLayout);
    layout->addWidget(console);


    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    console->setPalette(p);

    contextFilter = new ContextFilterEngine(nodeSettings->tagAndOptionSettings);

    loadScrollSettings();
    loadTags();
    filterOnWindowChanged();
    connect(nodeSettings->tagAndOptionSettings, SIGNAL(optionAdded(Tag*,TagOption*)),this,SLOT(optionAdded(Tag*,TagOption*)));
    connect(nodeSettings, SIGNAL(clearConsole()),this,SLOT(clearConsole()));

    connect(nodeSettings->tagAndOptionSettings, SIGNAL(tagsChanged()),this,SLOT(loadTags()));
    connect(nodeSettings,SIGNAL(maxLinesChanged()),this,SLOT(loadMaxLines()));
    connect(nodeSettings,SIGNAL(scrollSettingsChanged()),this,SLOT(loadScrollSettings()));
    connect(nodeSettings,SIGNAL(filterOnWindowChanged()),this,SLOT(filterOnWindowChanged()));


}
FilteredConsole::~FilteredConsole()
{
    delete contextFilter;
    contextFilter = nullptr;

    //VisualNodeBase decontructor will be called afterwards
    //it will delete the node using the baseNode pointer, set the node pointer to 0 to prevent a dangling pointer
    nodeSettings = nullptr;
}

NodeSettingsBase *FilteredConsole::getNodeSettings()
{
    return nodeSettings;
}
bool FilteredConsole::filterData(QString* destination, CircularBufferReader *bufferReader, QTextCharFormat *format)
{
    auto lambda = [&](char character) mutable {destination->append(character);};
    auto cargeReturnLambda = [&]() mutable {
        if(destination->length() > 0)
        {
            if(destination->at(destination->length()-1) == QChar('\r')){
                destination->chop(1);
                return true;
            }
        }
        return false;
    };
    ANSICodes ansiCodes;
    return contextFilter->filterDataWithStyle(lambda, cargeReturnLambda, bufferReader, format);
}
void FilteredConsole::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = filterData(&result, source->bufferReader, &currentCharFormat);

    if(nodeSettings->getAutoScrollEnabled())
    {
        console->moveCursor(QTextCursor::End);
        console->setCurrentCharFormat(oldFormat);
        console->insertPlainText(result);
        console->moveCursor(QTextCursor::End);
    }
    else {
        QTextCursor cursor = console->textCursor();

        cursor.movePosition(QTextCursor::End);
        cursor.setCharFormat(oldFormat);
        cursor.insertText(result);
    }


    if(styleChanged)
    {
        //when ansi is found the filter stops searching and is perhaps not empty, read it again
        NotifyBufferUpdate(source);
    }
}

void FilteredConsole::loadTags()
{
    while(tagComboBoxes.size() > 0)delete tagComboBoxes.takeAt(0);

    QListIterator<Tag*> tagIterator(nodeSettings->tagAndOptionSettings->tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        TagComboBox* newTagComboBox = new TagComboBox(currentTag);
        tagComboBoxes.append(newTagComboBox);
        newTagComboBox->loadTag();
        verticalLayout->addWidget(newTagComboBox);
    }
}
void FilteredConsole::optionAdded(Tag *destinationTag, TagOption *option)
{
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
void FilteredConsole::filterOnWindowChanged()
{
    if(nodeSettings->getFilterOnWindow())
    {
        QListIterator<TagComboBox*> comboBoxIterator(tagComboBoxes);
        while(comboBoxIterator.hasNext())
        {
            TagComboBox* currentTag = comboBoxIterator.next();
            currentTag->show();
        }
    }
    else {
        QListIterator<TagComboBox*> comboBoxIterator(tagComboBoxes);
        while(comboBoxIterator.hasNext())
        {
            TagComboBox* currentTag = comboBoxIterator.next();
            currentTag->hide();
        }
    }
}
void FilteredConsole::loadScrollSettings()
{
    if(nodeSettings->getHorizontalScroll() == HorizontalScrollOptions::scrollbar)
    {
        console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
    else {
        console->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        if(nodeSettings->getHorizontalScroll() == HorizontalScrollOptions::ignore)
        {
            console->setLineWrapMode(QPlainTextEdit::NoWrap);

        }
        else if(nodeSettings->getHorizontalScroll() == HorizontalScrollOptions::newline)
        {
            console->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        }
    }
}
void FilteredConsole::loadMaxLines()
{
    console->document()->setMaximumBlockCount(nodeSettings->getMaxLines());
}
void FilteredConsole::clearConsole()
{
    console->clear();
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
