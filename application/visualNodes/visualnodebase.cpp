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

void VisualNodeBase::addInputConnector()
{
    Connector* connector = new Connector(this, 0, height/2,ConnectorType::INPUT,10);
    connectors.append(connector);
}

void VisualNodeBase::addOutputConnector()
{
    Connector* connector = new Connector(this, width, height/2,ConnectorType::OUTPUT,10);
    connectors.append(connector);
}
bool VisualNodeBase::requestConnection(Connector *connector)
{
    qDebug("[debug][VisualNodeBase] request connection");
    if(connector->type == ConnectorType::OUTPUT)
    {
        return true;
    }
    else if(connector->type == ConnectorType::INPUT)
    {
        int count = 0;
        if(connector->connections.size() == 0)
        {
            return true;
        }
    }
    return false;
}
void VisualNodeBase::drawConnectors(QPainter* painter)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        painter->setPen(QColor::fromRgbF(0.6, 0.6, 0.6, 0.7));
        painter->setBrush(QColor::fromRgbF(1, 1, 1, 0.7));
        painter->drawEllipse(connector->getRect(0));
    }
}

void VisualNodeBase::paintBase(QPainter* painter, NodeStyleBase* nodeStyle, QString name)
{
    setPos(centerX-width/2,centerY-height/2);
    QRectF rect = innerRect();

    painter->setPen(nodeStyle->nodeBackgroundColor);
    painter->setBrush(nodeStyle->nodeBackgroundColor);

    painter->drawRoundRect(rect,10,10);

    painter->setPen(nodeStyle->nodeCategoryColor);
    painter->setBrush(nodeStyle->nodeCategoryColor);

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

    qDebug("[info,VisualNodeBase] press");
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->getRect(5).contains(event->pos()))
        {
            emit connectorPressed(this,connector);
            pressedOnConnection = true;
        }
    }
    if(!pressedOnConnection)
    {
        if(!isSelected())
        {
            selectedItems.clear();
            selectedItems.append(this);
        }
    }
    QGraphicsItem::mousePressEvent(event);

}
void VisualNodeBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!pressedOnConnection)
    {
        QPointF p = event->scenePos();
        centerX = p.x();
        centerY = p.y();
    }
}
void VisualNodeBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[info,VisualNodeBase] release");
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->getRect(5).contains(event->pos()))
        {
            emit connectorReleased(this,connector);
            pressedOnConnection = true;
        }
    }
    pressedOnConnection = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisualNodeBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
