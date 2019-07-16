#include "inputnode.h"

InputNode::InputNode()
{

}

void InputNode::notifyUnsubscribe(Subscription *subscription)
{
    subScriptions.removeOne(subscription);
}

void InputNode::addSubscription(OutputNode *outputNode)
{
    subScriptions.append(outputNode->subscribe(this));
}
