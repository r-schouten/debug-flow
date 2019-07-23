#include "visualsourcenodebase.h"

VisualSourceNodeBase::VisualSourceNodeBase()
{

}
void VisualSourceNodeBase::drawStartStop(QPainter *painter,bool running)
{
    drawStartStop(painter,width-20,3,running);
}

void VisualSourceNodeBase::drawStartStop(QPainter *painter, int x, int y, bool running)
{
    if(running)
    {
        QPainterPath path;
        path.moveTo (x, y);
        path.lineTo (x, y + 14);

        path.lineTo (x + 12, y + 7);

        path.lineTo (x, y);

        painter->setPen (Qt :: NoPen);
        painter->fillPath (path, QBrush (QColor ("green")));
    }
    else {
        painter->setBrush(QColor::fromRgbF(0.8,0.3,0.3,1));
        painter->drawRect(x,y+2,10,10);
    }
}

bool VisualSourceNodeBase::startStopClicked(QPointF mousePos)
{
    QRectF iconRect = QRectF(width-20,3,14,14);
    return iconRect.contains(mousePos);
}
