#pragma once
#include "inputnode.h"
#include "outputnode.h"

class ContextFilterNode : public InputNode, public OutputNode
{
public:
    ContextFilterNode();
    NodeSettingsBase *getNodeSettings();
    void NotifyBufferUpdate(Subscription *source);
};

