#pragma once
#include "circularbuffer.h"
#include "outputnode.h"
#include "subscription.h"
#include "nodebase.h"
#include "updatemanager.h"

class OutputNode;
class Subscription;
class NodeBase;

class InputNode:public virtual NodeBase
{
public:
    InputNode();
    virtual ~InputNode();
    virtual UpdateReturn_t NotifyBufferUpdate(Subscription* source) = 0;
    virtual void notifyHistoricalUpdateFinished();
    void notifyUnsubscribe(Subscription* subscription);
    void addSubscription(OutputNode* outputNode);
    void deleteSubscription(OutputNode* outputNode);

    void resetBufferReader(Subscription* caller);
    void bufferReaderToBegin(Subscription* caller);

    virtual std::string getNodeName();
    QList<Subscription *>* getSubScriptions();

    void lock();
    void unlock();

    bool isLocked();

    bool areAllOtherSubscriptionsUpdated(UpdateNr_t updateNr, Subscription *currentSubscription);
protected:
    QList<Subscription*> subScriptions;
 private:
    bool locked = false;
};

