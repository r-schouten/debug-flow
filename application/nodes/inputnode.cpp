#include "inputnode.h"

InputNode::InputNode()
{

}
CircularBufferReader* InputNode::getCircularBufferReader()
{
    return circularBuffer->requestNewReader();
}
