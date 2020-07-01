#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{
    circularBuffer = new CircularBuffer(dbgLogger);
    settings = new ContextFilterSettings(dbgLogger);
    connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings,dbgLogger);

}

ContextFilterNode::~ContextFilterNode()
{
    delete settings;
    settings = nullptr;
    delete contextFilterEngine;
}
ContextFilterSettings *ContextFilterNode::getNodeSettings()
{
    return settings;
}

bool ContextFilterNode::filterData(CircularBuffer* buffer, CircularBufferReader *bufferReader)
{
    auto lambda = [&](char character) mutable {buffer->appendByte(&character);};
    return contextFilterEngine->filterData(lambda, bufferReader);
}

void ContextFilterNode::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }
    filterData(circularBuffer, source->bufferReader);
    notifyAllSubscriptions();
}

void ContextFilterNode::initiateHistoricalUpdate()
{

    leftHistoricalUpdateOccured();

    if(hasInput)
    {
        dynamic_cast<InputNode*>(this)->leftForwardHistoricalUpdate();
    }
}
//called because an node connected to the input has changed settings
void ContextFilterNode::leftHistoricalUpdateOccured()
{
    dbgLogger->debug("ContextFilterNode", __FUNCTION__,"called");


    if(hasOutput)
    {
        dynamic_cast<OutputNode*>(this)->rightForwardHistoricalUpdate();
    }
}
