#include "outputnode.h"

OutputNode::OutputNode()
{
    hasOutput = true;
}

OutputNode::~OutputNode()
{
    QListIterator<Subscription*> iterator(subscribers);
    while(iterator.hasNext())
    {
        iterator.next()->remove();
    }
    if(circularBuffer != nullptr)
    {
        delete circularBuffer;
        circularBuffer = nullptr;
    }
}

Subscription* OutputNode::subscribe(InputNode *inputNode)
{
    if(inputNode == nullptr)
    {
        qFatal("[Fatal,OutputNode] subscribe() : inputNode == nullptr ");
    }
    if(circularBuffer == nullptr)
    {
        qFatal("[Fatal,OutputNode] circularBuffer == nullptr");
    }
    CircularBufferReader* reader = circularBuffer->requestNewReader();
    Subscription* subscription = new Subscription(inputNode, this, reader);
    subscribers.append(subscription);
    return subscription;
}

void OutputNode::notifyUnsubscribe(Subscription *subscription)
{
    subscribers.removeOne(subscription);
}
void OutputNode::notifyAllSubscriptions()
{
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
        i.next()->notifyBufferUpdate();
}

void OutputNode::rightForwardHistoricalUpdate()
{
    this->circularBuffer->reset();

    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
        i.next()->notifyHistoricalUpdate();
}

