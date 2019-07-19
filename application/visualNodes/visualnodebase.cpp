#include "visualnodebase.h"

VisualNodeBase::VisualNodeBase()
{
    selectionManager = SelectionManager::getInstance();
    setFlag(QGraphicsItem::ItemIsMovable, false);
}
VisualNodeBase::~VisualNodeBase()
{
    emit onDelete(this);
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        delete iterator.next();
    }
};
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
    Connector* connector = new Connector(this, 0, height/2,ConnectorType::INPUT,10,M_PI);
    connectors.append(connector);
}

void VisualNodeBase::addOutputConnector()
{
    Connector* connector = new Connector(this, width, height/2,ConnectorType::OUTPUT,10,0);
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
#ifdef ALLOW_MULTIPLE_INPUT
        return true;
#else
        if(connector->connections.size() == 0)
        {
            return true;
        }
#endif
    }
    return false;
}
bool VisualNodeBase::requestConnection(Connector *connector, VisualConnection* connection)
{
    qDebug("[debug][VisualNodeBase] request connection");
    if(connector->type == ConnectorType::OUTPUT)
    {
        if(connection->getConnector1()->type == ConnectorType::OUTPUT)//can't connect output to output
        {
            return false;
        }

        return true;
    }
    else if(connector->type == ConnectorType::INPUT)
    {
        if(connection->getConnector1()->type == ConnectorType::INPUT)//can't connect output to output
        {
            return false;
        }
#ifdef ALLOW_MULTIPLE_INPUT
        return true;
#else
        if(connector->connections.size() == 0)
        {
            return true;
        }
#endif
    }
    return false;
}

void VisualNodeBase::drawConnectors(QPainter* painter,NodeStyleBase* nodeStyle)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        painter->setPen(nodeStyle->connectorPen);
        painter->setBrush(nodeStyle->connectorBrush);
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

    QPen pen;
    if(isSelected())
    {
        pen = QPen(nodeStyle->selectedBorderPen);
    }
    else {
        pen = QPen(nodeStyle->borderPen);
    }
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundRect(rect,10,10);


    painter->setFont(nodeStyle->titleFont);
    painter->setPen(nodeStyle->titlePen);
    painter->drawText(titleRect,Qt::AlignCenter, name);
}

bool VisualNodeBase::isSelected()
{
    return selectionManager->isSelected(this);
}

void VisualNodeBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    //qDebug("[info,VisualNodeBase] press");
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
        if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton)
        {
            selectionManager->setSelected(this,false);
        }
        else {
            if(isSelected())
            {
                selectionManager->setSelected(this,false);
            }
            else {
                selectionManager->setSelected(this,true);
            }
        }
    }

}
void VisualNodeBase::moveBy(QPointF& by)
{
    centerX += by.x();
    centerY += by.y();
}
void VisualNodeBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("[info,VisualNodeBase] release");
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
}

void VisualNodeBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
