#include "outputnode.h"

OutputNode::OutputNode()
{

}

void OutputNode::addParentNode(InputNode *parent)
{
    parentNode = parent;
    bufferReader = parent->getCircularBufferReader();
    if(bufferReader == nullptr)
    {
        qFatal("OutputNode::addParentNode() : bufferReader == nullptr");
    }
}
