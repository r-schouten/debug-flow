#pragma once
#include "inputnode.h"
#include "outputnode.h"
class NodeBase
{
public:
    NodeBase();
    bool hasInput = false;
    bool hasOutput = false;
};

