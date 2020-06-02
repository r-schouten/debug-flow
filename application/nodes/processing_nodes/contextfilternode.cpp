#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode()
{
    circularBuffer = new CircularBuffer(500,1000);
    settings = new ContextFilterSettings();

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings);

}

ContextFilterSettings *ContextFilterNode::getNodeSettings()
{
    return settings;
}

void ContextFilterNode::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    contextFilterEngine->filterData(&result, source->bufferReader, nullptr);

    QByteArray bytes= result.toLatin1();
    circularBuffer->append(&bytes);
    NotifyAllSubscriptions();
}
