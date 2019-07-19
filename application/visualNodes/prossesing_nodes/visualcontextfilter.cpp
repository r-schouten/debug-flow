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

VisualNodeBase *VisualContextFilter::clone()
{
    return new VisualContextFilter;
}
void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,"context filter");
    drawConnectors(painter,this);
}
