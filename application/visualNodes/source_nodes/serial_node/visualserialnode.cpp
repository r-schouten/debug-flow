#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{
    node = new SerialNode();
    baseNode = node;
    name = "Serial node";
    shortDiscription = "this node provide acces to serial ports";
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
    activated = true;
}
void VisualSerialNode::openPort()
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
    if(node->settings->nodeSettings.running)
    {
        height = 80;
    }
    else {
        height = 100;
    }
    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);
    drawStartStop(painter,node->settings->nodeSettings.running);
}
void VisualSerialNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(startStopClicked(event->pos()))
    {
        if(node->settings->nodeSettings.running)
        {
            node->closeSerialPort();
        }
        else {
            openPort();
        }
    }
    else {
        VisualSourceNodeBase::mousePressEvent(event);
    }
}

QWidget *VisualSerialNode::loadPropertiesWidget(QWidget* parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new SerialNodePropertiesWidget(parent, node);
    }
    else {
        qDebug("[warn][VisualSerialNode] propertywidget already exist");
    }
    return propertyWidget;
}

void VisualSerialNode::releasePropertiesWidget()
{
    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}
