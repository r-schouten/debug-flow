#pragma once

#include <QMutexLocker>

#include "circularbuffer.h"
#include "nodeInput.h"
#include "subscription.h"
#include "updatemanager.h"

class NodeInput;
class Subscription;
class NodeBase;
class NodeOutput
{
public:
    NodeOutput(UpdateManager* updateManager, CircularBuffer* circularBuffer, DbgLogger* dbgLogger, NodeBase* parent);
    virtual ~NodeOutput();
    void notifyUnsubscribe(Subscription* subscription);
    QVector<Subscription *>* getSubscribers();

    void resetBuffer();
    bool bufferHistoricalCapable();
    void doHistoricalUpdate();

    UpdateReturn_t notifyAllSubscriptions();
    int getBufferUnusedSize();

    bool isProcessingDone() const;

    NodeBase *getParent() const;

    CircularBuffer *getCircularBuffer() const;

    bool processingDone = true;//this variable indicates whether all data did fit in the output buffer, or wheter a second buffer write is needed.
                                    //care about this variable, when processing done stays false this may result in a infinite loop somewere, or it triggers a safetey meganism
private:
    Subscription* subscribe(NodeInput* inputNode);

    QVector<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;

    NodeBase* parent = nullptr;
    UpdateManager* updateManager = nullptr;
    DbgLogger* dbgLogger = nullptr;

    friend NodeInput;
    friend NodeBase;
    friend NodeInfoViewer;
};

