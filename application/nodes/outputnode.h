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
    QList<Subscription *>* getSubscribers();
    virtual std::string getNodeName();

    void resetBuffer();
    bool bufferHistoricalCapable();
    void doHistoricalUpdate();

    void notifyAllSubscriptions();
    int getBufferUnusedSize();

    bool isProcessingDone() const;

protected:
    QList<Subscription*> subscribers;
    CircularBuffer* circularBuffer = nullptr;

    bool processingDone = false;//this variable indicates whether all data did fit in the output buffer, or wheter a second buffer write is needed.
                                //care about this variable, when processing done stays false this may result in a infinite loop somewere, or it triggers a safetey meganism
private:
    Subscription* subscribe(InputNode* inputNode);
    friend InputNode;
    friend NodeBase;
};

