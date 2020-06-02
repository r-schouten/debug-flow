#pragma once
#include "inputnode.h"
#include "outputnode.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
class ContextFilterNode : public InputNode, public OutputNode
{
public:
    ContextFilterNode();
    virtual ~ContextFilterNode();
    ContextFilterSettings *getNodeSettings();
    void NotifyBufferUpdate(Subscription *source);

private:
    bool filterData(CircularBuffer *destination, CircularBufferReader *bufferReader);

    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;

};

