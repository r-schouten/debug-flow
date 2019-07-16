#include "visualnodebase.h"
QList<VisualNodeBase*> VisualNodeBase::selectedItems;
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
QRectF VisualNodeBase::getLeftConnection()
{
    return QRect(0-connectionDiameter/2, height/2-connectionDiameter/2, connectionDiameter, connectionDiameter);
}
QRectF VisualNodeBase::getRightConnection()
{
    return QRect(width-connectionDiameter/2, height/2-connectionDiameter/2, connectionDiameter, connectionDiameter);
}
void VisualNodeBase::drawConnectionLeft(QPainter* painter)
{
    painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
    painter->setBrush(QColor::fromRgbF(1, 1, 1, 0.7));
    painter->drawEllipse(getLeftConnection());
}
void VisualNodeBase::drawConnectionRight(QPainter* painter)
{
    painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
    painter->setBrush(QColor::fromRgbF(1, 1, 1, 0.7));
    painter->drawEllipse(getRightConnection());
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

    if(isSelected())
    {
        painter->setPen(QColor::fromRgbF(0.2, 0.6, 0.7, 0.7));
    }
    else {
        painter->setPen(QColor::fromRgbF(0.3, 0.3, 0.3, 0.7));
    }
    painter->setBrush(Qt::NoBrush);

    painter->drawRoundRect(rect,10,10);

    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QColor::fromRgbF(1, 1, 1, 1));
    painter->drawText(titleRect,Qt::AlignCenter, name);
}

bool pressedOnConnection = false;
bool VisualNodeBase::isSelected()
{
    return selectedItems.contains(this);
}

void VisualNodeBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(!isSelected())
    {
        selectedItems.clear();
        selectedItems.append(this);
    }
}
void VisualNodeBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(getLeftConnection().marginsAdded(QMargins(5,5,5,5)).contains(event->pos()))
    {
        qDebug("[info,VisualNodeBase] leftconnection contains scenepos");
        pressedOnConnection = true;
    }
    else if(getRightConnection().marginsAdded(QMargins(5,5,5,5)).contains(event->pos()))
    {
        qDebug("[info,VisualNodeBase] rigthconnection contains scenepos");
        pressedOnConnection = true;

    }
    else
    {
        if(!pressedOnConnection)
        {
            QPointF p = event->scenePos();
            x = p.x();
            y = p.y();
        }
    }
}

void VisualNodeBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressedOnConnection = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisualNodeBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
