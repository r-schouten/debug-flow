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

void InputNode::notifyHistoricalUpdateFinished()
{
    //do nothing, this function can be optionally overrided
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
std::string InputNode::getNodeName()
{
    return "InputNode";
}

QList<Subscription *>* InputNode::getSubScriptions()
{
    return &subScriptions;
}

//------historical update feature--------
void InputNode::resetBufferReader(Subscription *caller)
{
    caller->bufferReader->reset();
}

void InputNode::bufferReaderToBegin(Subscription *caller)
{
    dbgLogger->debug("InputNode",__FUNCTION__,"called");
    caller->bufferReader->toBegin();
}

bool InputNode::areAllOtherSubscriptionsUpdated(UpdateNr_t updateNr, Subscription* currentSubscription)
{
    if(subScriptions.length() <= 1)return true;
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        if(subscription != currentSubscription)
        {
            if(subscription->getUpdateNr() != updateNr)
            {
                return false;
            }
        }
    }
    return true;
}
void InputNode::lock()
{
    locked = true;
}

void InputNode::unlock()
{
    locked = false;
}

bool InputNode::isLocked()
{
    return locked;
}

