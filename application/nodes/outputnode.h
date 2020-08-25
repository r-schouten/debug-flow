#pragma once

#include <QMutexLocker>

#include "circularbuffer.h"
#include "inputnode.h"
#include "subscription.h"
#include "nodebase.h"
#include "updatemanager.h"

class InputNode;
class Subscription;
class NodeBase;
class OutputNode: public virtual NodeBase
{
public:
    OutputNode();
    virtual ~OutputNode();
    void notifyUnsubscribe(Subscription* subscription);
    QList<Subscription *>* getSubscribers();
    virtual std::string getNodeName();

    void resetBuffer();
    bool bufferHistoricalCapable();
    void doHistoricalUpdate();

    UpdateReturn_t notifyAllSubscriptions();
    int getBufferUnusedSize();


protected:
    QList<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;

private:
    Subscription* subscribe(InputNode* inputNode);


    friend InputNode;
    friend NodeBase;
    friend NodeInfoViewer;
};

