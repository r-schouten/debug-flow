#include "visualnodebase.h"

VisualNodeBase::VisualNodeBase()
{
    selectionManager = SelectionManager::getInstance();
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(ItemIsSelectable, false);
    setAcceptHoverEvents(true);
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
bool VisualNodeBase::recursiveCircularDependencyCheck(VisualNodeBase* originNode)
{
    bool circularDepencencyDetected = false;
    QListIterator<Connector*> iterator(this->connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->type == ConnectorType::OUTPUT)
        {
            QListIterator<VisualConnection*> iterator2(connector->connections);
            while(iterator2.hasNext())
            {
                VisualConnection* currentConnection = iterator2.next();
                Connector* inputConnector = nullptr;
                if((currentConnection->getConnector1()!=nullptr)&&(currentConnection->getConnector1()->type == ConnectorType::INPUT))
                {
                    inputConnector = currentConnection->getConnector1();
                }
                else if((currentConnection->getConnector2()!=nullptr)&&(currentConnection->getConnector2()->type == ConnectorType::INPUT))
                {
                    inputConnector = currentConnection->getConnector2();
                }
                else {
                    qDebug("[error][recursiveCircularDependencyCheck] no input connector");
                    break;
                }
                if(inputConnector->getParent() == originNode)
                {
                    circularDepencencyDetected = true;
                    return circularDepencencyDetected;
                }
                circularDepencencyDetected = inputConnector->getParent()->recursiveCircularDependencyCheck(originNode);
                if(circularDepencencyDetected)
                {
                    return circularDepencencyDetected;
                }
            }
        }
    }
    return circularDepencencyDetected;

}
bool VisualNodeBase::requestConnection(Connector *connector, VisualConnection* connection)
{
    if(connection->getSetConnector() == connector)
    {
        return false;
    }

    if(connector->type == ConnectorType::OUTPUT)
    {

        if(connection->getSetConnector()->getParent()->recursiveCircularDependencyCheck(this))
        {
            qDebug("[info][requestConnection] circular dependency detected on output");
            return false;
        }
        if(connection->getSetConnector()->type == ConnectorType::OUTPUT)//can't connect output to output
        {
            return false;
        }


        return true;
    }
    else if(connector->type == ConnectorType::INPUT)
    {
        if(recursiveCircularDependencyCheck(connection->getSetConnector()->getParent()))
        {
            qDebug("[info][requestConnection] circular dependency detected on output");
            return false;
        }

        if(connection->getSetConnector()->type == ConnectorType::INPUT)//can't connect output to output
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
        if(selectionManager->hoveredConnector == connector)
        {
            painter->setPen(Qt::NoPen);
            if(*selectionManager->currentTrackingConnection == nullptr)//not drawing a connection
            {
                painter->setBrush(QColor::fromRgbF(1,1,0,0.3));
            }
            else {
                if(requestConnection(connector,*selectionManager->currentTrackingConnection))//valid connection
                {
                    painter->setBrush(QColor::fromRgbF(0,1,0,0.3));
                }
                else {//invalid connection
                    painter->setBrush(QColor::fromRgbF(1,0,0,0.3));
                }
            }
            painter->drawEllipse(connector->getRect(10));


            painter->setPen(nodeStyle->connectorPen);
            painter->setBrush(QColor::fromRgbF(1,1,0,0.7));
            painter->drawEllipse(connector->getRect(0));
        }
        else {
            painter->setPen(nodeStyle->connectorPen);
            painter->setBrush(nodeStyle->connectorBrush);
            painter->drawEllipse(connector->getRect(0));
        }


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
        }
    }
    pressedOnConnection = false;
}

void VisualNodeBase::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->getRect(5).contains(event->pos()))
        {
            selectionManager->hoveredConnector = connector;
        }
        else {
            if(selectionManager->hoveredConnector == connector)
            {
                selectionManager->hoveredConnector = nullptr;
            }
        }
    }
}

void VisualNodeBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(selectionManager->hoveredConnector == connector)
        {
            selectionManager->hoveredConnector = nullptr;
        }
    }
}



