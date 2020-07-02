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

void InputNode::leftForwardHistoricalUpdate()
{
    dbgLogger->debug("InputNode", __FUNCTION__,"called");

    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        subscription->getOutputNode()->notifyLeftHistoricalUpdate();
    }
}

void InputNode::inputNotifyHistoricalUpdate(Subscription *subscription)
{
    //the buffer reader is already resetted

    dbgLogger->debug("InputNode", __FUNCTION__,"called");

    this->leftHistoricalUpdateOccured();
}
