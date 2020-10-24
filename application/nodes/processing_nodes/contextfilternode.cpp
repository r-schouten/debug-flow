#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager *historicalUpdateManager)
    :NodeBase(updateManager,dbgLogger),historcalUpdateManager(historicalUpdateManager)
{
    circularBuffer = new CircularBuffer(dbgLogger, "ContextFilter");
    nodeInput = new NodeInput(updateManager, dbgLogger, this);
    nodeInput->setDoBufferUpdateCallback(std::bind(&ContextFilterNode::doBufferUpdate,this,std::placeholders::_1,std::placeholders::_2));

    nodeOutput = new NodeOutput(updateManager,circularBuffer, dbgLogger, this);
    settings = new ContextFilterSettings(dbgLogger);
    connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings,dbgLogger);
}

ContextFilterNode::~ContextFilterNode()
{
    delete nodeInput;
    delete nodeOutput;
    delete settings;
    settings = nullptr;
    delete contextFilterEngine;
}

std::string ContextFilterNode::getNodeName()
{
    return CLASSNAME;
}

ContextFilterSettings *ContextFilterNode::getNodeSettings()
{
    return settings;
}

UpdateReturn_t ContextFilterNode::doBufferUpdate(Subscription *source, int availableSize)
{
#ifdef QT_DEBUG
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }
#endif
    auto lambda = [&](char character) mutable {circularBuffer->appendByte(character);};

    updateManager->measurementPoint(CONTEXT_FILTER_BEGIN);
    contextFilterEngine->filterData(lambda, source->bufferReader, availableSize, nodeOutput->getBufferUnusedSize(),&nodeOutput->processingDone, &metaData);
    updateManager->measurementPoint(CONTEXT_FILTER_END);

    UpdateReturn_t updateReturn = nodeOutput->notifyAllSubscriptions();
    if(updateReturn == UpdateReturn_t::ROUTE_DELAYED)
    {
            return updateReturn;
    }
    if(nodeOutput->processingDone)
    {
        return UpdateReturn_t::UPDATE_DONE;
    }
    else
    {
        return UpdateReturn_t::NOT_DONE;
    }
}

void ContextFilterNode::reset()
{

}

void ContextFilterNode::initiateHistoricalUpdate()
{
    historcalUpdateManager->initatiateHistoricalUpdate(this);
}
