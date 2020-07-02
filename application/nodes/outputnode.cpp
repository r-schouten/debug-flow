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

void OutputNode::resetBuffer()
{
    circularBuffer->reset();
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        subscription->getInputNode()->resetBufferReader(subscription);
    }
}

bool OutputNode::bufferHistoricalCapable()
{
    circularBuffer->isHistoricalCapable();
}

void OutputNode::doHistoricalUpdate()
{
    dbgLogger->debug("OutputNode",__FUNCTION__,"called");
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        if(subscription->getInputNode()->isLocked())
        {

        }
        else
        {
            subscription->getInputNode()->bufferReaderToBegin(subscription);
        }
    }
}

QList<Subscription *>* OutputNode::getSubscribers()
{
    return &subscribers;
}

std::string OutputNode::getNodeName()
{
    return "OutputNode";
}

