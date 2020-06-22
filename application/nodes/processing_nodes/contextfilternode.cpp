#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{
    circularBuffer = new CircularBuffer(dbgLogger);
    settings = new ContextFilterSettings(dbgLogger);

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
    auto lambda = [&](char character) mutable {buffer->append(&character, 1);};
    return contextFilterEngine->filterData(lambda, bufferReader);
}

void ContextFilterNode::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }
    filterData(circularBuffer, source->bufferReader);
    NotifyAllSubscriptions();
}
