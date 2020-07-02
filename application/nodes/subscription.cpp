#include "subscription.h"
#include "inputnode.h"
#include "outputnode.h"
InputNode *Subscription::getInputNode() const
{
    return inputNode;
}

Subscription::~Subscription()
{
    inputNode->notifyUnsubscribe(this);
    outputNode->notifyUnsubscribe(this);
    delete bufferReader;
}

OutputNode *Subscription::getOutputNode()
{
    return outputNode;
}
void Subscription::remove()//use a function instead of a deconstructor so the caller don't have to delete the object
{
    delete this;
}
void Subscription::notifyBufferUpdate()
{
    inputNode->NotifyBufferUpdate(this);
}
