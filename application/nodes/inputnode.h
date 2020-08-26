#pragma once
#include "circularbuffer.h"
#include "outputnode.h"
#include "subscription.h"
#include "nodebase.h"
#include "updatemanager.h"
#include "mergehelper.h"

class OutputNode;
class Subscription;
class NodeBase;

class InputNode:public virtual NodeBase
{
public:
    InputNode();
    virtual ~InputNode();
    void notifyBufferUpdate(Subscription* source);
    virtual void doBufferUpdate(Subscription* source, int availableSize) = 0;
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

protected:
    QList<Subscription*> subScriptions;
 private:
    void doMergeUpdate();
    bool areAllOtherSubscriptionsUpdated(UpdateNr_t updateNr, Subscription *currentSubscription);

    bool locked = false;
    MergeHelper* mergeHelper = nullptr;
    Subscription *findOldest();
    bool allSubsReady();
};

