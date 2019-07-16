#include "outputnode.h"

OutputNode::OutputNode()
{
    nodeHaveOutput = true;
}

Subscription* OutputNode::subscribe(InputNode *inputNode)
{
    if(inputNode == nullptr)
    {
        qFatal("OutputNode::subscribe() : inputNode == nullptr ");
    }
    if(circularBuffer == nullptr)
    {
        qFatal("OutputNode::subscribe() circularBuffer == nullptr");
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
void OutputNode::NotifyAllSubscriptions()
{
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
        i.next()->notifyBufferUpdate();
}

