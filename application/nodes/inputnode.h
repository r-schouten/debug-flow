#pragma once
#include "circularbuffer.h"
#include "outputnode.h"
#include "subscription.h"
class OutputNode;
class Subscription;
class InputNode : public NodeBase
{

public:
    InputNode();
    virtual void NotifyBufferUpdate(Subscription* source) = 0;
    void notifyUnsubscribe(Subscription* subscription);
    void addSubscription(OutputNode* outputNode);

protected:
    QList<Subscription*> subScriptions;
    CircularBufferReader* bufferReader;
};

