#include "testgeneratornode.h"


TestGeneratorNode::TestGeneratorNode(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :NodeBase(updateManager, dbgLogger)
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
    //general
    activated = true;
    circularBuffer = new CircularBuffer(dbgLogger,"TestGenerator", TEST_GENERATOR_BUFFER_SIZE, TEST_GENERATOR_MAX_BUFFER_SIZE, true);
    metaDataHelper = new MetaDataHelper;

    //timer
    updateTimer = new QTimer(this);
    connect(settings, SIGNAL(threadSettingsChanged()),this, SLOT(threadSettingsChanged()));
    connect(settings, SIGNAL(updateRateChanged()),this, SLOT(updateRateChanged()));

    updateTimer->start(settings->getUpdateRate());

    //lambda for the from thread notify setting
    auto notifyLambda = [&]() mutable {notifyAllSubscriptions();};


    worker = new TestGeneratorWorker(settings, circularBuffer, notifyLambda);
    workerFromThread = new TestGeneratorWorker(settings, circularBuffer, notifyLambda);
    workerThread = new QThread;
    workerFromThread->moveToThread(workerThread);
    workerThread->start();

    updateTimer->moveToThread(workerThread);

    connect(worker, SIGNAL(updateDone()),this, SLOT(updateDone()));
    connect(workerFromThread, SIGNAL(updateDone()),this, SLOT(updateDone()));


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
    updateManager->initateUpdate();
    //dbgLogger->verbose(CLASSNAME,__FUNCTION__,"start update with %d bytes",settings->getDataPerUpdate());
    while(notifyAllSubscriptions() != UpdateReturn_t::UPDATE_DONE);
//    dbgLogger->verbose(CLASSNAME,__FUNCTION__,"update done\n\n\n");
    updateManager->finishUpdate();
}
void TestGeneratorNode::processInMainThread()
{
    worker->process();
}
void TestGeneratorNode::threadSettingsChanged()
{
    if(settings->getFromThread())
    {
        disconnect(updateTimer, SIGNAL(timeout()), worker, SLOT(process()));
        connect(updateTimer, SIGNAL(timeout()), workerFromThread, SLOT(process()));

    }
    else
    {
        disconnect(updateTimer, SIGNAL(timeout()), workerFromThread, SLOT(process()));
        connect(updateTimer, SIGNAL(timeout()), worker, SLOT(process()));

    }
}
