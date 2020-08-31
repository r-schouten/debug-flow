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
    QVector<Subscription *>* getSubscribers();
    virtual std::string getNodeName();

    void resetBuffer();
    bool bufferHistoricalCapable();
    void doHistoricalUpdate();

    UpdateReturn_t notifyAllSubscriptions();
    inline int getBufferUnusedSize()
    {
        return circularBuffer->unUsedSize();
    }

    bool isProcessingDone() const;

protected:
    QVector<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;

    bool processingDone = true;//this variable indicates whether all data did fit in the output buffer, or wheter a second buffer write is needed.
                                    //care about this variable, when processing done stays false this may result in a infinite loop somewere, or it triggers a safetey meganism
private:
    Subscription* subscribe(InputNode* inputNode);


    friend InputNode;
    friend NodeBase;
    friend NodeInfoViewer;
};

