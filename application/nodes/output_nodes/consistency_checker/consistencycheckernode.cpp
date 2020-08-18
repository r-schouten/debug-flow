#include "consistencycheckernode.h"


ConsistencyCheckerNode::ConsistencyCheckerNode(DbgLogger *dbgLogger, HistoricalUpdateManager* historcalUpdateManager)
    :NodeBase(dbgLogger),historcalUpdateManager(historcalUpdateManager)
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
    delete settings;
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

}
void ConsistencyCheckerNode::NotifyBufferUpdate(Subscription *source)
{
    //callback function/lambda to add data to the result string

    auto addCharLambda = [&](char character) mutable {bufferString.append(character);};

    auto formatChangedLambda = [&]() mutable
    {
        if(bufferString.endsWith("\n"))
        {
            appendConsole(bufferString);
            bufferString.clear();
        }
    };
    QTextCharFormat format;
    MetaData_t metadata;

    contextFilterEngine->filterDataWithStyle(addCharLambda, formatChangedLambda,  source->bufferReader, &format, &metadata);
}
void ConsistencyCheckerNode::appendConsole(QString line)
{
    QString textPart = line.left(match.length());
    if(textPart.compare(match,textPart) == 0)
    {
        QTextCharFormat format;
        format.setForeground(Qt::green);

        if(settings->getShowAll())
        {
            console->moveCursor(QTextCursor::End);
            console->setCurrentCharFormat(format);
            console->insertPlainText(textPart);
            console->moveCursor(QTextCursor::End);
        }
        QString numberpart = line.right(line.length()-textPart.length()+1);
        bool oke = true;
        //QRegExp rx("\\d+");
        //numberpart = numberpart.section(rx,0);
        int number = numberpart.toInt(&oke);
        if(!oke)
        {
            format.setForeground(Qt::red);
        }
        lastNr++;
        if(lastNr != number)
        {
            lastNr = number;
            format.setForeground(Qt::red);
            oke = false;
        }
        if((oke == false) || (settings->getShowAll()))
        {
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

