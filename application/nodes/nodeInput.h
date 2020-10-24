#pragma once
#include "circularbuffer.h"
#include "nodeoutput.h"
#include "subscription.h"
#include "updatemanager.h"
#include "mergehelper.h"

using namespace std;

class NodeOutput;
class Subscription;

class NodeInput
{
public:
    NodeInput(UpdateManager* updateManager, DbgLogger* dbgLogger, NodeBase* parent);
    ~NodeInput();

    //called from NodeOutput
    UpdateReturn_t notifyBufferUpdate(Subscription* source);
    //called from NotifyBufferUpdate
    void notifyHistoricalUpdateFinished();

    void notifyUnsubscribe(Subscription* subscription);
    void addSubscription(NodeOutput* outputNode);
    void deleteSubscription(NodeOutput* outputNode);

    QVector<Subscription *> *getSubScriptions();

    void lock();
    void unlock();
    bool isLocked();

    NodeBase *getParent() const;

    void setDoBufferUpdateCallback(const std::function<UpdateReturn_t (Subscription *, int)> &value);
    void resetBufferReader(Subscription* caller);
    void bufferReaderToBegin(Subscription* caller);

private:
    UpdateReturn_t doMergeUpdate(Subscription *source);
    Subscription *findOldest();
    bool allSubsReady();

    QVector<Subscription*> subScriptions;
    NodeBase* parent = nullptr;
    bool locked = false;
    MergeHelper* mergeHelper = nullptr;
    UpdateManager* updateManager = nullptr;
    DbgLogger* dbgLogger = nullptr;


    std::function<UpdateReturn_t(Subscription*, int)> doBufferUpdateCallback;
    std::function<void()> historicalUpdateFinshedCallback;
};

