#include "visualnodebase.h"

VisualNodeBase::VisualNodeBase()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

QRectF VisualNodeBase::boundingRect() const
{
    return QRectF(0,0,width,height);
}


void VisualNodeBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void VisualNodeBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    x = p.x();
    y = p.y();
}

void VisualNodeBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisualNodeBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
