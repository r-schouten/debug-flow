#include "testgeneratornode.h"


TestGeneratorNode::TestGeneratorNode(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{
    settings = new TestGeneratorSettings(dbgLogger);

}

TestGeneratorNode::~TestGeneratorNode()
{
    delete settings;
    if(activated)
    {
        workerThread->quit();
        workerThread->wait();
    }
}
void TestGeneratorNode::activate()
{
    activated = true;
    circularBuffer = new CircularBuffer(dbgLogger, TEST_GENERATOR_BUFFER_SIZE, TEST_GENERATOR_MAX_BUFFER_SIZE, true);
    metaDataHelper = new MetaDataHelper;

    updateTimer = new QTimer(this);
    connect(settings, SIGNAL(threadSettingsChanged()),this, SLOT(threadSettingsChanged()));
    connect(settings, SIGNAL(updateRateChanged()),this, SLOT(updateRateChanged()));

    updateTimer->start(settings->getUpdateRate());

    worker = new TestGeneratorWorker(settings, circularBuffer);
    workerThread = new QThread;
    worker->moveToThread(workerThread);

    threadSettingsChanged();

}
void TestGeneratorNode::updateRateChanged()
{
    updateTimer->stop();
    updateTimer->start(settings->getUpdateRate());
}
//implement for debug purposes
std::string TestGeneratorNode::getNodeName()
{
    return "TestGeneratorNode";
}

TestGeneratorSettings* TestGeneratorNode::getNodeSettings()
{
    return settings;
}

void TestGeneratorNode::reset()
{

}
void TestGeneratorNode::updateDone()
{
    notifyAllSubscriptions();
}
void TestGeneratorNode::processInMainThread()
{
    worker->process();
    notifyAllSubscriptions();
}
void TestGeneratorNode::threadSettingsChanged()
{
    if(settings->getFromThread())
    {
        disconnect(updateTimer, nullptr, this, nullptr);

        //connect(workerThread, SIGNAL(started()), worker, SLOT(initialize()));
        connect(updateTimer, SIGNAL(timeout()), worker, SLOT(process()));
        connect(worker, SIGNAL(updateDone()),this, SLOT(updateDone()));
        connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
        connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        workerThread->start();
    }
    else
    {
        disconnect(updateTimer, nullptr, worker, nullptr);
        disconnect(worker, SIGNAL(updateDone()));

        connect(updateTimer, SIGNAL(timeout()), this, SLOT(processInMainThread()));

    }
}
