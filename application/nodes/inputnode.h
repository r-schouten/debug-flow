#pragma once
#include "circularbuffer.h"
#include "outputnode.h"
#include "subscription.h"
#include "nodebase.h"
#include "updatemanager.h"
#include "mergehelper.h"

using namespace std;

class OutputNode;
class Subscription;
class NodeBase;

class InputNode:public virtual NodeBase
{
public:
    InputNode();
    virtual ~InputNode();
    virtual UpdateReturn_t notifyBufferUpdate(Subscription* source);
    virtual UpdateReturn_t doBufferUpdate(Subscription* source, int availableSize) = 0;
    virtual void notifyHistoricalUpdateFinished();
    void notifyUnsubscribe(Subscription* subscription);
    void addSubscription(OutputNode* outputNode);
    void deleteSubscription(OutputNode* outputNode);

    void resetBufferReader(Subscription* caller);
    void bufferReaderToBegin(Subscription* caller);

    virtual std::string getNodeName();
    QVector<Subscription *> *getSubScriptions();

    void lock();
    void unlock();

    bool isLocked();

protected:
    QVector<Subscription*> subScriptions;
 private:
    UpdateReturn_t doMergeUpdate(Subscription *source);

    bool locked = false;
    MergeHelper* mergeHelper = nullptr;
    Subscription *findOldest();
    bool allSubsReady();
};

