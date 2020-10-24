#include "nodeoutput.h"

NodeOutput::NodeOutput(UpdateManager *updateManager,CircularBuffer* circularBuffer, DbgLogger *dbgLogger, NodeBase *parent)
    :updateManager(updateManager), circularBuffer(circularBuffer), dbgLogger(dbgLogger), parent(parent)
{

}

NodeOutput::~NodeOutput()
{
    QVectorIterator<Subscription*> iterator(subscribers);
    while(iterator.hasNext())
    {
        delete iterator.next();
    }
    if(circularBuffer != nullptr)
    {
        delete circularBuffer;
        circularBuffer = nullptr;
    }
}

Subscription* NodeOutput::subscribe(NodeInput *inputNode)
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

void NodeOutput::notifyUnsubscribe(Subscription *subscription)
{
    subscribers.removeOne(subscription);
}


QVector<Subscription *>* NodeOutput::getSubscribers()
{
    return &subscribers;
}

//-------buffer update-----------
UpdateReturn_t NodeOutput::notifyAllSubscriptions()
{
    UpdateReturn_t updateReturn = UpdateReturn_t::UPDATE_DONE;
    circularBuffer->resetTail();//part of the tail tracking feature, this doesn't modify the buffer itself
    QVectorIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        UpdateReturn_t currentReturn = subscription->notifyBufferUpdate();
        if(currentReturn == UpdateReturn_t::ROUTE_DELAYED)
            updateReturn = currentReturn;
        circularBuffer->calcTail(subscription->bufferReader);//tail tracking
    }
    return updateReturn;
}

int NodeOutput::getBufferUnusedSize()
{
    return circularBuffer->unUsedSize();
}



bool NodeOutput::isProcessingDone() const
{
    return processingDone;
}

NodeBase *NodeOutput::getParent() const
{
    return parent;
}

CircularBuffer *NodeOutput::getCircularBuffer() const
{
    return circularBuffer;
}

//-------historical update feature----------
void NodeOutput::resetBuffer()
{
    circularBuffer->reset();
    QVectorIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        subscription->getInput()->resetBufferReader(subscription);
    }
}
bool NodeOutput::bufferHistoricalCapable()
{
    return circularBuffer->isHistoricalCapable();
}

void NodeOutput::doHistoricalUpdate()
{
    dbgLogger->debug("OutputNode",__FUNCTION__,"called");
    QVectorIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        if(subscription->getInput()->isLocked())
        {

        }
        else
        {
            subscription->getInput()->bufferReaderToBegin(subscription);
        }
    }
}

