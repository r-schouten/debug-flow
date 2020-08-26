#include "filteredconsole.h"

FilteredConsole::FilteredConsole(UpdateManager* updateManager, HistoricalUpdateManager *historcalUpdateManager,DbgLogger *dbgLogger)
   :NodeBase(updateManager,dbgLogger),historcalUpdateManager(historcalUpdateManager)
{
    //initialize settings
    nodeSettings = new FilteredNodeSettings(dbgLogger);

    //make textEdit filed
    console = new ConsoleWidget(this);
    loadMaxLines();
    SideLineOptionsChanged();

    //layout for filter selection widgets
    layout = new QVBoxLayout(this);
    verticalLayout = new QHBoxLayout(this);

    layout->addLayout(verticalLayout);
    layout->addWidget(console);

    //use the context filter engine for filtering
    contextFilter = new ContextFilterEngine(nodeSettings->tagAndOptionSettings, dbgLogger);

    //load stuff from the settings
    loadScrollSettings();
    loadTags();
    filterOnWindowChanged();

    //for the filtering
    connect(nodeSettings->tagAndOptionSettings, SIGNAL(optionAdded(Tag*,TagOption*)),this,SLOT(optionAdded(Tag*,TagOption*)));

    //signals from the propertiesWidget
    connect(nodeSettings, SIGNAL(clearConsole()),this,SLOT(clearConsole()));

    connect(nodeSettings->tagAndOptionSettings, SIGNAL(tagsChanged()),this,SLOT(loadTags()));
    connect(nodeSettings,SIGNAL(maxLinesChanged()),this,SLOT(loadMaxLines()));
    connect(nodeSettings,SIGNAL(scrollSettingsChanged()),this,SLOT(loadScrollSettings()));
    connect(nodeSettings,SIGNAL(filterOnWindowChanged()),this,SLOT(filterOnWindowChanged()));
    connect(nodeSettings,SIGNAL(SideLineOptionsChanged()),this,SLOT(SideLineOptionsChanged()));

    //slot the initialize an historical update
    connect(nodeSettings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));

    bufferString.reserve(100);
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

std::string FilteredConsole::getNodeName()
{
    return CLASSNAME;
}

void FilteredConsole::reset()
{
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"called");
    nodeSettings->clearConsoleClicked();
    clearConsole();
}
void FilteredConsole::filterData(int availableSize)
{
    //callback function/lambda to add data to the result string
    auto addCharLambda = [&](char character) mutable {bufferString.append(character);};

    auto formatChangedLambda = [&]() mutable
    {
        //function to prevent a split between /r and /n, which would result in an extra linebreak
        if(bufferString.endsWith(QChar('\r'))){
            bufferString.chop(1);
        }
        console->append(bufferString, currentCharFormat, &metaData, nodeSettings->getAutoScrollEnabled());
        bufferString.clear();
    };
    contextFilter->filterDataWithStyle(addCharLambda, formatChangedLambda,  lastSource->bufferReader, availableSize, &currentCharFormat, &metaData);
    formatChangedLambda();
}
void FilteredConsole::doBufferUpdate(Subscription *source, int availableSize)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }

    lastSource = source;
    if(thread() != QThread::currentThread())
    {
        QMetaObject::invokeMethod(this, "filterData" , Qt::QueuedConnection);
    }
    else
    {
        filterData(availableSize);
    }

}
//------historical update functions--------
void FilteredConsole::initiateHistoricalUpdate()
{
    historcalUpdateManager->initatiateHistoricalUpdate(this);
}
void FilteredConsole::notifyHistoricalUpdateFinished()
{
    QString text = "----historical update done----\n";
    QTextCharFormat format;
    format.setForeground(Qt::gray);

    console->append(text, format, &metaData, nodeSettings->getAutoScrollEnabled());
}

//-----tag and option functions
void FilteredConsole::loadTags()
{
    while(tagComboBoxes.size() > 0)delete tagComboBoxes.takeAt(0);

    QListIterator<Tag*> tagIterator(nodeSettings->tagAndOptionSettings->tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        connect(currentTag, SIGNAL(dataChanged(Tag*)), this, SLOT(dataChanged()));
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
        connect(destinationTag, SIGNAL(dataChanged(Tag*)), this, SLOT(dataChanged()));
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

void FilteredConsole::dataChanged()
{
     nodeSettings->notifySettingsChanged(DATA_INVALID, DONT_SAVE, NODE);
}

//-------callbacks for changed settings-------
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
    console->setMaxLines(nodeSettings->getMaxLines());
}

void FilteredConsole::clearConsole()
{
    console->clear();
}
void FilteredConsole::SideLineOptionsChanged()
{
    if((nodeSettings->getSideLineOptions() == SideLineOptions::LINENUMBERS)||(nodeSettings->getSideLineOptions() == SideLineOptions::BOTH))
    {
        console->setLineNumbersEnabled(true);
    }
    else
    {
        console->setLineNumbersEnabled(false);
    }
    if((nodeSettings->getSideLineOptions() == SideLineOptions::TIME)||(nodeSettings->getSideLineOptions() == SideLineOptions::BOTH))
    {
        console->setTimeEnabled(true);
    }
    else
    {
        console->setTimeEnabled(false);
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
