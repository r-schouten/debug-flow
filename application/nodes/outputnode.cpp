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


QList<Subscription *>* OutputNode::getSubscribers()
{
    return &subscribers;
}

std::string OutputNode::getNodeName()
{
    return "OutputNode";
}


//-------buffer update-----------
void OutputNode::notifyAllSubscriptions()
{
    QMutexLocker locker(&mutex);
    circularBuffer->resetTail();//part of the tail tracking feature, this doesn't modify the buffer itself
    QListIterator<Subscription*> i(subscribers);
    while (i.hasNext())
    {
        Subscription* subscription = i.next();
        subscription->notifyBufferUpdate();
        OutputNode* outputNode = dynamic_cast<OutputNode*>(subscription->getInputNode());

        //todo: this code might have problems when merging is supported
        if(outputNode)//if it is a node which is having an output(so an own buffer)
        {
            while(outputNode->isProcessingDone() == false)
            {
                //save variables for the safety mechanism, when this doesn't change the node has a bug with the processingDone variable
                int previousIteration = subscription->bufferReader->getIteration();
                int previousTail = subscription->bufferReader->getTail();

                dbgLogger->debug("OutputNode", __FUNCTION__,"isProcessingDone false, calling notifyBufferUpdate() again");
                subscription->notifyBufferUpdate();
                if(outputNode->isProcessingDone() == true)break;
                if((previousIteration == subscription->bufferReader->getIteration()) && (previousTail == subscription->bufferReader->getTail()))
                {
                    dbgLogger->fatal("OutputNode", __FUNCTION__, "safety mechanism triggered, node has processingDone not set but doensn't do anything\ncaused by node:%s",subscription->getInputNode()->getNodeName().c_str());
                }
            }
        }
        circularBuffer->calcTail(subscription->bufferReader);//tail tracking
    }
}

int OutputNode::getBufferUnusedSize()
{
    return circularBuffer->unUsedSize();
}

bool OutputNode::isProcessingDone() const
{
    return processingDone;
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

