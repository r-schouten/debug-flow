#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter(SceneComponents* sceneComponents)
    :VisualNodeBase(sceneComponents)
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
    contextFilter = new ContextFilter();
}
VisualContextFilter::~VisualContextFilter()
{
    if(node)
    {
        delete node;
        baseNode = nullptr;
    }
}

void VisualContextFilter::activate()
{

}
VisualNodeBase *VisualContextFilter::clone()
{
    return new VisualContextFilter(sceneComponents);
}

void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}
