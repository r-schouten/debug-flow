#include "visualtestgeneratornode.h"


VisualTestGeneratorNode::VisualTestGeneratorNode(FlowObjects *_flowObjects)
    :VisualSourceNodeBase(_flowObjects)
{
    construct();
}

VisualTestGeneratorNode::VisualTestGeneratorNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualSourceNodeBase(_flowObjects, baseJson, handler)
{
     Q_UNUSED(derivedJson)
     construct();
     settings->deserialize(settingsJson, handler);
}

VisualTestGeneratorNode::~VisualTestGeneratorNode()
{
    //VisualNodeBase decontructor will be called afterwards
    //it will delete the node using the baseNode pointer, set the node pointer to 0 to prevent a dangling pointer
    node = nullptr;
}

void VisualTestGeneratorNode::construct()
{
    node = new TestGeneratorNode(dbgLogger);
    baseNode = node;

    settings = node->getNodeSettings();

    connect(settings, SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));

    name = "test data generator";
    shortDiscription = "this node generates data for test purposes";
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
VisualNodeBase *VisualTestGeneratorNode::clone()
{
    return new VisualTestGeneratorNode(flowObjects);
}

//the resource list makes node instances just for the paint function.
//in such case the activate function is not called and memory or performance wasting things should not be activated
void VisualTestGeneratorNode::activate()
{
    activated = true;
    node->activate();
}

//serialize every variable which need to be saved, and which is owned by this (derived) node
//JSON_NODE_TYPE is deserialized by the loadstore class.
QJsonObject *VisualTestGeneratorNode::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_NODE_TYPE, CLASSNAME);

    return jsonObject;
}
//deserialization handler not added yet because there are no variables to deserialize

//used by loadstore to deserialize nodes
bool VisualTestGeneratorNode::classNameEquals(QString name)
{
    if(name.compare(staticMetaObject.className(),Qt::CaseInsensitive) == 0)
    {
        return true;
    }
    return false;
}

PropertyWidgetBase *VisualTestGeneratorNode::loadPropertiesWidget(QWidget *parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new TestGeneratorPropertiesWidget(parent, dbgLogger, node->getNodeSettings());
    }
    else {
        dbgLogger->warning(CLASSNAME,__FUNCTION__,"propertywidget already exist");
    }
    return propertyWidget;
}

void VisualTestGeneratorNode::releasePropertiesWidget()
{
    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualTestGeneratorNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void VisualTestGeneratorNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    VisualSourceNodeBase::mousePressEvent(event);
}




