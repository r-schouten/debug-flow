#include "subscription.h"
#include "inputnode.h"
#include "outputnode.h"
Subscription::~Subscription()
{
    inputNode->notifyUnsubscribe(this);
    outputNode->notifyUnsubscribe(this);
    delete bufferReader;
}

void Subscription::notifyBufferUpdate()
{
    inputNode->NotifyBufferUpdate(this);
}
