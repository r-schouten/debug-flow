#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{
    node = new SerialNode();
}
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,QColor::fromRgbF(0.7, 0.7, 0.3, 0.7),"Serial");
    if(node->nodeHaveInput)
    {
        drawConnectionLeft(painter);
    }
    if(node->nodeHaveOutput)
    {
        drawConnectionRight(painter);
    }

}
