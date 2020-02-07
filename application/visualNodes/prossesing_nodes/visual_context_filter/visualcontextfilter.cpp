#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter()
{
    node = new ContextFilterNode();
    baseNode = node;

    name = "Context filter";
    shortDiscription = QString("this node provides filtering for %1 context").arg(CONTEXT_STYLE_NAME);
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
    if(node)
    {
        delete node;
        baseNode = nullptr;
    }
}
PropertyWidgetBase *VisualContextFilter::loadPropertiesWidget(QWidget* parent)
{
    return nullptr;
}

void VisualContextFilter::releasePropertiesWidget()
{

}

void VisualContextFilter::activate()
{

}
VisualNodeBase *VisualContextFilter::clone()
{
    return new VisualContextFilter();
}

void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

QJsonObject *VisualContextFilter::serialize(SerializationSettings_t &serialisationSettings, SerializationHandler &serialisationErrorLog)
{
    return nullptr;
}

