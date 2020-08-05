#include "visualtamplatenode.h"


VisualTamplateNode::VisualTamplateNode(FlowObjects *_flowObjects)
    :VisualSourceNodeBase(_flowObjects)
{
    construct();
}

VisualTamplateNode::VisualTamplateNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualSourceNodeBase(_flowObjects, baseJson, handler)
{
     Q_UNUSED(derivedJson)
     construct();
     settings->deserialize(settingsJson, handler);
}

VisualTamplateNode::~VisualTamplateNode()
{
    //VisualNodeBase decontructor will be called afterwards
    //it will delete the node using the baseNode pointer, set the node pointer to 0 to prevent a dangling pointer
    node = nullptr;
}

void VisualTamplateNode::construct()
{
    node = new TamplateNode(dbgLogger);
    baseNode = node;

    settings = node->getNodeSettings();

    connect(settings, SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));

    name = "tamplate node";
    shortDiscription = "an easy start for building a node";
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

//create a new instance of such node, this function is used to make a new node from the resourceList.
VisualNodeBase *VisualTamplateNode::clone()
{
    return new VisualTamplateNode(flowObjects);
}

//the resource list makes node instances just for the paint function.
//in such case the activate function is not called and memory or performance wasting things should not be activated
void VisualTamplateNode::activate()
{
    activated = true;
    //node->activate();
}

//serialize every variable which need to be saved, and which is owned by this (derived) node
//JSON_NODE_TYPE is deserialized by the loadstore class.
QJsonObject *VisualTamplateNode::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_NODE_TYPE, CLASSNAME);

    return jsonObject;
}
//deserialization handler not added yet because there are no variables to deserialize

//used by loadstore to deserialize nodes
bool VisualTamplateNode::classNameEquals(QString name)
{
    if(name.compare(staticMetaObject.className(),Qt::CaseInsensitive) == 0)
    {
        return true;
    }
    return false;
}

PropertyWidgetBase *VisualTamplateNode::loadPropertiesWidget(QWidget *parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new TamplateNodePropertiesWidget(parent, dbgLogger, settings);
    }
    else {
        dbgLogger->warning(CLASSNAME,__FUNCTION__,"propertywidget already exist");
    }
    return propertyWidget;
}

void VisualTamplateNode::releasePropertiesWidget()
{
    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualTamplateNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setRenderHints(QPainter::TextAntialiasing, true);

    paintBase(painter,this,"generator");
    drawConnectors(painter, this);


    painter->setPen(textPen);
    painter->setFont(textFont);

}

void VisualTamplateNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    VisualSourceNodeBase::mousePressEvent(event);
}




