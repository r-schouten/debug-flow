#pragma once
#include "circularbuffer.h"
#include "inputnode.h"
#include "subscription.h"

class InputNode;
class Subscription;
class OutputNode
{
public:
    OutputNode();
    Subscription* subscribe(InputNode* inputNode);
    void notifyUnsubscribe(Subscription* subscription);
protected:
    void NotifyAllSubscriptions();
    QList<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;

};

