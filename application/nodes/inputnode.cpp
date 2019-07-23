#include "inputnode.h"

InputNode::InputNode()
{

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
