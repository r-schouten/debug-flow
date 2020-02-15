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
    delete node;
    node = nullptr;
    baseNode = nullptr;
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
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

QJsonObject *VisualContextFilter::serialize(SerializationHandler &handler)
{
    return nullptr;
}

