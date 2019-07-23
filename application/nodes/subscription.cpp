#include "subscription.h"
#include "inputnode.h"
#include "outputnode.h"
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
    //qDebug("notifyBufferUpdate");
    inputNode->NotifyBufferUpdate(this);
}
