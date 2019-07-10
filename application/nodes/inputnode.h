#pragma once

#include "nodebase.h"
#include "circularbuffer.h"

class InputNode : public NodeBase
{

public:
    InputNode();
    CircularBufferReader *getCircularBufferReader();
protected:
    CircularBuffer* circularBuffer;
};

