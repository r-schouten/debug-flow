#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter()
{
    node = new ContextFilter();
    name = "Context filter";
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
    }
}
NodeBase* VisualContextFilter::getNode()
{
    return node;
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
