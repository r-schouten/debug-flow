#pragma once
#include "nodebase.h"
#include "inputnode.h"
#include "circularbuffer.h"

class OutputNode : public NodeBase
{
public:
    OutputNode();
    void addParentNode(InputNode *parent);
    virtual void notifyBufferUpdate() = 0;
protected:
    NodeBase* parentNode;
    CircularBufferReader* bufferReader;

};

