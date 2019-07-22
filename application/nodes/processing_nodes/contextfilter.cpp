#include "contextfilter.h"

ContextFilter::ContextFilter()
{
    circularBuffer = new CircularBuffer(500,1000);
    if(dynamic_cast<InputNode*>(this))
    {
        hasInput = true;
    }
    if(dynamic_cast<OutputNode*>(this))
    {
        hasOutput = true;
    }
}

void ContextFilter::NotifyBufferUpdate(Subscription *source)
{
    qDebug("[verbose,ContextFilter] NotifyBufferUpdate");

    int availableSize = source->bufferReader->availableSize();
    for(int i=0;i<availableSize;i++)
    {
        circularBuffer->append(&source->bufferReader->at(i),1);

    }
    source->bufferReader->release(availableSize);
    NotifyAllSubscriptions();
}
