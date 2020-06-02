#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter(FlowObjects *_flowObjects)
    :VisualNodeBase(_flowObjects)
{
    construct();
}

VisualContextFilter::VisualContextFilter(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualNodeBase(_flowObjects)
{
    construct();
}
void VisualContextFilter::construct()
{
    node = new ContextFilterNode();
    baseNode = node;

    name = "Context filter";
    shortDiscription = QString("this node provides filtering for %1 context").arg(CONTEXT_STYLE_NAME);

    settings = node->getNodeSettings();
    connect(node->getNodeSettings(), SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));

    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
}
VisualContextFilter::~VisualContextFilter()
{
    delete node;
    node = nullptr;
    baseNode = nullptr;
}
PropertyWidgetBase *VisualContextFilter::loadPropertiesWidget(QWidget* parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new VisualContextFilterPropertiesWidget(parent, settings);
    }
    else {
        qDebug("[warn][VisualSerialNode] propertywidget already exist");
    }
    return propertyWidget;
}

void VisualContextFilter::releasePropertiesWidget()
{
    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualContextFilter::activate()
{
    activated = true;
}
VisualNodeBase *VisualContextFilter::clone()
{
    return new VisualContextFilter(flowObjects);
}

void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

QJsonObject *VisualContextFilter::serialize(SerializationHandler &handler)
{
    return nullptr;
}

