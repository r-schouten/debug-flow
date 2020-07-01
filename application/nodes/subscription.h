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
    ~Subscription();
public:
    Subscription(InputNode* _inputNode, OutputNode* _outputNode, CircularBufferReader* reader)
        :inputNode(_inputNode),outputNode(_outputNode),bufferReader(reader)
    {

    }
    OutputNode* getOutputNode();
    void notifyBufferUpdate();
    void notifyHistoricalUpdate();
    CircularBufferReader* bufferReader;

    void remove();

};

