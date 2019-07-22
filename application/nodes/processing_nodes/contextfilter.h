#pragma once
#include "inputnode.h"
#include "outputnode.h"

class ContextFilter : public InputNode, public OutputNode
{
public:
    ContextFilter();

public:
    void NotifyBufferUpdate(Subscription *source);
};

