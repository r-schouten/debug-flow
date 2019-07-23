#pragma once
#include "circularbuffer.h"
#include "outputnode.h"
#include "subscription.h"
#include "nodebase.h"

class OutputNode;
class Subscription;
class NodeBase;

class InputNode:public virtual NodeBase
{

public:
    InputNode();
    ~InputNode();
    virtual void NotifyBufferUpdate(Subscription* source) = 0;
    void notifyUnsubscribe(Subscription* subscription);

    void addSubscription(OutputNode* outputNode);

    void deleteSubscription(OutputNode* outputNode);
protected:;
    QList<Subscription*> subScriptions;
};

