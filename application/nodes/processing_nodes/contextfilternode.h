#pragma once
#include "inputnode.h"
#include "outputnode.h"

class ContextFilterNode : public InputNode, public OutputNode
{
public:
    ContextFilterNode();

public:
    void NotifyBufferUpdate(Subscription *source);
};

