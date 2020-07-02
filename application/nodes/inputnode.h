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
    virtual ~InputNode();
    virtual void NotifyBufferUpdate(Subscription* source) = 0;
    void notifyUnsubscribe(Subscription* subscription);
    void addSubscription(OutputNode* outputNode);
    void deleteSubscription(OutputNode* outputNode);

    void resetBufferReader(Subscription* caller);
    void bufferReaderToBegin(Subscription* caller);

    virtual std::string getNodeName();
    QList<Subscription *>* getSubScriptions();

    void lock();
    bool isLocked();

protected:
    QList<Subscription*> subScriptions;
 private:
    bool locked = false;
};

