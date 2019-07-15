#include "visualserialnode.h"

VisualSerialNode::VisualSerialNode()
{

}
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x-width/2,y-height/2);
    QRectF rect = boundingRect();

    painter->setPen(QColor::fromRgb(170,170,150));
    painter->setBrush(QColor::fromRgb(170,170,150));

    painter->drawRoundRect(rect,10,10);

    painter->setPen(QColor::fromRgb(190,190,70));
    painter->setBrush(QColor::fromRgb(190,190,70));

    painter->drawRoundRect(0,0,width,20, 10,10);

    painter->setPen(QColor::fromRgb(50,50,50));
    painter->setBrush(Qt::NoBrush);

    painter->drawRoundRect(rect,10,10);

}
