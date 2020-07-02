#pragma once
#include "circularbuffer.h"
#include "inputnode.h"
#include "subscription.h"
#include "nodebase.h"

class InputNode;
class Subscription;
class NodeBase;
class OutputNode: public virtual NodeBase
{
public:
    OutputNode();
    virtual ~OutputNode();
    void notifyUnsubscribe(Subscription* subscription);
    void rightForwardHistoricalUpdate();
    void notifyLeftHistoricalUpdate();
protected:
    void notifyAllSubscriptions();

    QList<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;
private:
    Subscription* subscribe(InputNode* inputNode);
    friend InputNode;
};

