#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode()
{
    circularBuffer = new CircularBuffer(500,1000);
}

NodeSettingsBase *ContextFilterNode::getNodeSettings()
{
    return nullptr;//todo add settings
}

void ContextFilterNode::NotifyBufferUpdate(Subscription *source)
{
    //qDebug("[verbose,ContextFilter] NotifyBufferUpdate");

    int availableSize = source->bufferReader->availableSize();
    for(int i=0;i<availableSize;i++)
    {
        circularBuffer->append(&source->bufferReader->at(i),1);

    }
    source->bufferReader->release(availableSize);
    NotifyAllSubscriptions();
}
