#pragma once
#include "circularbuffer.h"
#include "nodebase.h"
#include "inputnode.h"
#include "outputnode.h"

class InputNode;
class OutputNode;
class Subscription
{
private:
    InputNode* inputNode;
    OutputNode* outputNode;
public:
    Subscription(InputNode* _inputNode, OutputNode* _outputNode, CircularBufferReader* reader)
        :inputNode(_inputNode),outputNode(_outputNode),bufferReader(reader)
    {}
    ~Subscription();
    void notifyBufferUpdate();
    CircularBufferReader* bufferReader;

};

