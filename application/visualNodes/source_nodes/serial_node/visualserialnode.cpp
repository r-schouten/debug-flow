#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{
    construct();
}

VisualSerialNode::VisualSerialNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualSourceNodeBase(baseJson, handler)
{
    construct();
}
void VisualSerialNode::construct()
{
    node = new SerialNode();
    baseNode = node;
    name = "Serial node";
    shortDiscription = "this node provide access to serial ports";
    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
    height = 80;
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
//    if(node->settings->nodeSettings.running)
//    {
//        height = 80;
//    }
//    else {
//        height = 100;
//    }
    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);
    drawStartStop(painter,node->settings->nodeSettings.running);

    painter->setPen(textPen);
    painter->setFont(textFont);

    if(node->settings->nodeSettings.running)
    {
        painter->drawText(QPointF(10,35),"connected");
    }
    else
    {
        painter->drawText(QPointF(10,35),"not connected");
    }
    if(node->settings->nodeSettings.name == "")
    {
        painter->drawText(QPointF(10,50),"click to configure");
    }
    else
    {
        if(node->settings->nodeSettings.errorOccured)
        {
            painter->setPen(errorPen);
            painter->drawText(QPointF(10,50),"error reading");
            painter->drawText(QPointF(10,65),node->settings->nodeSettings.errorString);
        }
        else
        {
            if(node->settings->nodeSettings.running)
            {
                painter->drawText(QPointF(10,50),node->settings->nodeSettings.name);
                painter->drawText(QPointF(10,65),QString::number(node->settings->nodeSettings.baudRate));
            }
            else {
                painter->drawText(QPointF(10,50),"click to configure");
            }
        }
    }

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
    VisualSourceNodeBase::mousePressEvent(event);
}

PropertyWidgetBase *VisualSerialNode::loadPropertiesWidget(QWidget* parent)
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
QJsonObject *VisualSerialNode::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_NODE_TYPE, CLASSNAME);

    return jsonObject;
}

bool VisualSerialNode::classNameEquals(QString name)
{
    if(name.compare(staticMetaObject.className(),Qt::CaseInsensitive) == 0)
    {
        return true;
    }
    return false;
}

