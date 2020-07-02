#include "inputnode.h"

InputNode::InputNode()
{
    hasInput = true;
}

InputNode::~InputNode()
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {

        iterator.next()->remove();
    }
}

void InputNode::notifyUnsubscribe(Subscription *subscription)
{
    subScriptions.removeOne(subscription);
}



void InputNode::addSubscription(OutputNode *outputNode)
{
    subScriptions.append(outputNode->subscribe(this));
}

void InputNode::deleteSubscription(OutputNode *outputNode)
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {

        Subscription* subscription = iterator.next();
        if(subscription->getOutputNode() == outputNode)
        {
            subscription->remove();
        }
    }
}

void InputNode::resetBufferReader(Subscription *caller)
{
    caller->bufferReader->reset();
}

void InputNode::bufferReaderToBegin(Subscription *caller)
{
    dbgLogger->debug("InputNode",__FUNCTION__,"called");
    caller->bufferReader->toBegin();
}

std::string InputNode::getNodeName()
{
    return "InputNode";
}

QList<Subscription *>* InputNode::getSubScriptions()
{
    return &subScriptions;
}

void InputNode::lock()
{
    locked = true;
}

bool InputNode::isLocked()
{
    return locked;
}

