#include "visualnodebase.h"

VisualNodeBase::VisualNodeBase()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

QRectF VisualNodeBase::boundingRect() const
{
    return QRectF(-5,0,width+10,height);
}
QRectF VisualNodeBase::innerRect() const
{
    return QRectF(0,0,width,height);
}
void VisualNodeBase::drawConnectionLeft(QPainter* painter)
{
    painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
    painter->setBrush(QColor::fromRgbF(1, 1, 1, 0.7));
    int diameter = 10;
    painter->drawEllipse(0-diameter/2, height/2-diameter/2, diameter, diameter);
}
void VisualNodeBase::drawConnectionRight(QPainter* painter)
{
    painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
    painter->setBrush(QColor::fromRgbF(1, 1, 1, 0.7));
    int diameter = 10;
    painter->drawEllipse(width-diameter/2, height/2-diameter/2, diameter, diameter);
}

void VisualNodeBase::paintBase(QPainter* painter, QColor baseColor, QString name)
{
    setPos(x-width/2,y-height/2);
    QRectF rect = innerRect();

    painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
    painter->setBrush(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));

    painter->drawRoundRect(rect,10,10);

    painter->setPen(baseColor);
    painter->setBrush(baseColor);

    QRect titleRect(0,0,width,20);
    painter->drawRoundRect(titleRect, 10,10);

    painter->setPen(QColor::fromRgbF(0.3, 0.3, 0.3, 0.7));
    painter->setBrush(Qt::NoBrush);

    painter->drawRoundRect(rect,10,10);

    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor::fromRgbF(1, 1, 1, 1));
    painter->drawText(titleRect,Qt::AlignCenter, name);
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
