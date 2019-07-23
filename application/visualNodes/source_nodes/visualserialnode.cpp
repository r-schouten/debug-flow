#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{
    node = new SerialNode();
    baseNode = node;
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
VisualSerialNode::~VisualSerialNode()
{
    if(node != nullptr)
    {
        delete node;
        baseNode = nullptr;
    }
}
void VisualSerialNode::activate()
{
    node->openSerialPort();

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

