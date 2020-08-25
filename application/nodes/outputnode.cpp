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
    Subscription* subscription = new Subscription(inputNode, this, reader, updateManager, dbgLogger);
    subscribers.append(subscription);
    return subscription;
}

void OutputNode::notifyUnsubscribe(Subscription *subscription)
{
    subscribers.removeOne(subscription);
}


QList<Subscription *>* OutputNode::getSubscribers()
{
    return &subscribers;
}

std::string OutputNode::getNodeName()
{
    return "OutputNode";
}


//-------buffer update-----------
UpdateReturn_t OutputNode::notifyAllSubscriptions()
{
    UpdateReturn_t updateReturn = UPDATE_DONE;
    circularBuffer->resetTail();//part of the tail tracking feature, this doesn't modify the buffer itself
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        UpdateReturn_t updateState = subscription->notifyBufferUpdate();
        if(updateState == ROUTE_DELAYED)
        {
            updateReturn = ROUTE_DELAYED;
        }
        circularBuffer->calcTail(subscription->bufferReader);//tail tracking
    }
    return updateReturn;
}

int OutputNode::getBufferUnusedSize()
{
    return circularBuffer->unUsedSize();
}


//-------historical update feature----------
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
    return circularBuffer->isHistoricalCapable();
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

