#include "visualcontextfilter.h"

VisualContextFilter::VisualContextFilter()
{
    node = new ContextFilter();
}
void VisualContextFilter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,QColor::fromRgbF(0.7, 0.3, 0.7, 0.7),"context filter");
    if(node->hasInput)
    {
        drawConnectionLeft(painter);
    }
    if(node->hasOutput)
    {
        drawConnectionRight(painter);
    }

}
