#include "outputnode.h"

OutputNode::OutputNode()
{

}

Subscription* OutputNode::subscribe(InputNode *inputNode)
{
    if(inputNode == nullptr)
    {
        qFatal("OutputNode::subscribe() : inputNode == nullptr ");
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

