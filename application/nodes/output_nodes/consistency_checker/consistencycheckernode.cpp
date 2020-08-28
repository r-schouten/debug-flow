#include "consistencycheckernode.h"


ConsistencyCheckerNode::ConsistencyCheckerNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager* historcalUpdateManager)
    :NodeBase(updateManager, dbgLogger),historcalUpdateManager(historcalUpdateManager)
{
    settings = new ConsistencyCheckerSettings(dbgLogger);

    tagAndOptionsSettings = new TagAndOptionsSettings();
    contextFilterEngine = new ContextFilterEngine(tagAndOptionsSettings,dbgLogger);


    layout = new QVBoxLayout(this);
    console = new QPlainTextEdit();


    layout->addWidget(console);

    connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));
}

ConsistencyCheckerNode::~ConsistencyCheckerNode()
{
    QMutexLocker locker(&classMutex);
    //VisualNodeBase decontructor will be called afterwards
    //it will delete the node using the baseNode pointer, set the node pointer to 0 to prevent a dangling pointer
    settings = nullptr;
    delete tagAndOptionsSettings;
    delete contextFilterEngine;
}


//implement for debug purposes
std::string ConsistencyCheckerNode::getNodeName()
{
    return "ConsistencyCheckerNode";
}

ConsistencyCheckerSettings* ConsistencyCheckerNode::getNodeSettings()
{
    return settings;
}

void ConsistencyCheckerNode::reset()
{
    console->clear();
    bufferString.clear();
}
UpdateReturn_t ConsistencyCheckerNode::doBufferUpdate(Subscription *source, int availableSize)
{
    //callback function/lambda to add data to the result string
    auto addCharLambda = [&](char character) mutable {
        bufferString.append(character);
        if(bufferString.endsWith("\n"))
        {
            updateManager->measurementPoint(VISUALIZE_BEGIN);
            bufferStringCopy = bufferString;
            bufferString.clear();
            appendConsole(bufferStringCopy);
            updateManager->measurementPoint(VISUALIZE_END);
        }
    };
    auto formatChangedLambda = [&]() mutable
    {

    };
    QTextCharFormat format;
    MetaData_t metadata;

    updateManager->measurementPoint(FILTER_WITH_STYLE_START);
    contextFilterEngine->filterDataWithStyle(addCharLambda, formatChangedLambda, source->bufferReader, availableSize, &format, &metadata);
    updateManager->measurementPoint(FILTER_WITH_STYLE_END);

}

void ConsistencyCheckerNode::appendConsole(QString line)
{
    line = line.replace('|',"");
    QString textPart = line.left(match.length());
    if(textPart.compare(match,textPart) == 0)
    {
        QTextCharFormat format;

        QString numberpart = line.right(line.length()-textPart.length()+1);
        bool oke = true;
        int number = numberpart.toInt(&oke);

        if((oke == false) || (settings->getShowAll()))
        {
            format.setForeground(Qt::green);
            console->moveCursor(QTextCursor::End);
            console->setCurrentCharFormat(format);
            console->insertPlainText(textPart);
            console->moveCursor(QTextCursor::End);

            if(!oke)
            {
                format.setForeground(Qt::red);
            }
            if(!((lastNr == number)||(lastNr+1 == number)))
            {
                format.setForeground(Qt::red);
                oke = false;
            }
            lastNr = number;
            console->moveCursor(QTextCursor::End);
            console->setCurrentCharFormat(format);
            console->insertPlainText(numberpart);
            console->moveCursor(QTextCursor::End);
        }
    }
    else
    {
        QTextCharFormat format;
        format.setForeground(Qt::red);
        console->moveCursor(QTextCursor::End);
        console->setCurrentCharFormat(format);
        console->insertPlainText(line);
        console->moveCursor(QTextCursor::End);
    }
}
void ConsistencyCheckerNode::initiateHistoricalUpdate()
{
    historcalUpdateManager->initatiateHistoricalUpdate(this);
}
void ConsistencyCheckerNode::notifyHistoricalUpdateFinished()
{

}

