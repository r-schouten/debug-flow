#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode(FlowObjects *_flowObjects)
    :VisualSourceNodeBase(_flowObjects)
{
    construct();
}

VisualSerialNode::VisualSerialNode(FlowObjects *_flowObjects,QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualSourceNodeBase(_flowObjects, baseJson, handler)
{
    Q_UNUSED(derivedJson);
    construct();
    serialSettings->deserialize(settingsJson, handler);
}
void VisualSerialNode::construct()
{
    node = new SerialNode(flowObjects->getDbgLogger());
    baseNode = node;

    serialSettings = node->getNodeSettings();

    connect(serialSettings, SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));

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
    //VisualNodeBase decontructor will be called afterwards
    //it will delete the node using the baseNode pointer, set the node pointer to 0 to prevent a dangling pointer
    node = nullptr;

}

//the resource list makes node instances just for the paint function.
//in such case the activate function is not called and memory or performance wasting things should not be activated
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
    return new VisualSerialNode(flowObjects);
}
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setRenderHints(QPainter::TextAntialiasing, true);

    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);
    drawStartStop(painter,serialSettings->running);

    painter->setPen(textPen);
    painter->setFont(textFont);

    if(serialSettings->running)
    {
        painter->drawText(QPointF(10,35),"connected");
    }
    else
    {
        painter->drawText(QPointF(10,35),"not connected");
    }
    if(serialSettings->name == "")
    {
        painter->drawText(QPointF(10,50),"click to configure");
    }
    else
    {
        if(serialSettings->errorOccured)
        {
            painter->setPen(errorPen);
            painter->drawText(QPointF(10,50),"error reading");
            painter->drawText(QPointF(10,65),serialSettings->errorString);
        }
        else
        {
            if(serialSettings->running)
            {
                painter->drawText(QPointF(10,50),serialSettings->name);
                painter->drawText(QPointF(10,65),QString::number(serialSettings->baudRate));
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
        if(serialSettings->running)
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
        propertyWidget = new SerialNodePropertiesWidget(parent, dbgLogger, node);
    }
    else {
        dbgLogger->warning(CLASSNAME,__FUNCTION__,"propertywidget already exist");
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
    Q_UNUSED(handler);
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

