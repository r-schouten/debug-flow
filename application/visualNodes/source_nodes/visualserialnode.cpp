#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{
    node = new SerialNode();
    name = "Serial node";
    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
}

VisualNodeBase* VisualSerialNode::clone()
{
    return new VisualSerialNode();
}
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);

    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);

}
