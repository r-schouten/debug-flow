#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode()
{
    circularBuffer = new CircularBuffer(500,1000);
    settings = new ContextFilterSettings();

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings);
}

ContextFilterNode::~ContextFilterNode()
{
    delete settings;
    settings = nullptr;
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
