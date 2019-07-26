#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter()
{
    node = new ContextFilterNode();
    baseNode = node;

    name = "Context filter";
    shortDiscription = "this node provides filtering for debug flow style context";
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
    return new VisualContextFilter;
}

void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}
