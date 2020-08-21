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

}
void ConsistencyCheckerNode::NotifyBufferUpdate(Subscription *source)
{
    QMutexLocker locker(&classMutex);
    lastSource = source;
    //callback function/lambda to add data to the result string
    auto addCharLambda = [&](char character) mutable {
        bufferString.append(character);
        if(bufferString.endsWith("\n"))
        {
            bufferStringCopy = bufferString;
            bufferString.clear();
            //QMetaObject::invokeMethod(this, "appendConsole" , Qt::QueuedConnection,Q_ARG(QString,bufferStringCopy));
            appendConsole(bufferStringCopy);
        }
    };
    auto formatChangedLambda = [&]() mutable
    {

    };
    QTextCharFormat format;
    MetaData_t metadata;

    contextFilterEngine->filterDataWithStyle(addCharLambda, formatChangedLambda,  lastSource->bufferReader, &format, &metadata);

//    if(thread() != QThread::currentThread())
//    {

//        return;
//    }
//    else
//    {
//        processUpdate();
//    }
}

void ConsistencyCheckerNode::appendConsole(QString line)
{
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
            lastNr++;
            if(lastNr != number)
            {
                lastNr = number;
                format.setForeground(Qt::red);
                oke = false;
            }
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

