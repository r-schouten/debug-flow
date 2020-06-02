#pragma once
#include "inputnode.h"
#include "outputnode.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
class ContextFilterNode : public InputNode, public OutputNode
{
public:
    ContextFilterNode();
    ContextFilterSettings *getNodeSettings();
    void NotifyBufferUpdate(Subscription *source);

private:
    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;
};

