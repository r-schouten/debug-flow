#include "visualnodebase.h"

VisualNodeBase::VisualNodeBase(FlowObjects *_flowObjects)
{
    flowObjects = _flowObjects;
    dbgLogger = flowObjects->getDbgLogger();
    selectionManager = flowObjects->getSelectionManager();
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(ItemIsSelectable, false);
    setAcceptHoverEvents(true);

    uniqueId = Utils::getRandom();
    dbgLogger->debug(CLASSNAME,__FUNCTION__,"got new id %lld", uniqueId);
}

VisualNodeBase::VisualNodeBase(FlowObjects *_flowObjects, QJsonObject &jsonObject, DeserializationHandler &handler)
    :VisualNodeBase(_flowObjects)
{
    deserializeBase(jsonObject, handler);
}
VisualNodeBase::~VisualNodeBase()
{
    //there is a image available that explains how a node is deleted
    emit onDelete(this);

    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        delete iterator.next();
    }

    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
    if(baseNode)
    {
        delete baseNode;
        baseNode = nullptr;
    }
};
QRectF VisualNodeBase::boundingRect() const
{
    return QRectF(-CONNECTOR_DIAMETER/2,0,width+CONNECTOR_DIAMETER,height);
}
QRectF VisualNodeBase::innerRect() const
{
    return QRectF(0,0,width,height);
}

void VisualNodeBase::addInputConnector()
{
    Connector* connector = new Connector(this, 0, height/2,ConnectorType::INPUT, CONNECTOR_DIAMETER,M_PI, "default input");
    connectors.append(connector);
}

void VisualNodeBase::addOutputConnector()
{
    Connector* connector = new Connector(this, width, height/2,ConnectorType::OUTPUT, CONNECTOR_DIAMETER,0, "default output");
    connectors.append(connector);
}
Connector* VisualNodeBase::findConnectorWithName(QString name)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* currentConnector = iterator.next();
        if(currentConnector->name.compare(name, Qt::CaseInsensitive) == 0)
        {
            return currentConnector;
        }
    }
    return nullptr;
}
void VisualNodeBase::makeConnection(VisualConnection* connection)
{
    //run requistConnection and recursiveDependancyCheck first!
#ifdef QT_DEBUG
    if(!requestConnection(connection->getConnector1(),connection->getConnector2(), true))
    {
        qFatal("[fatal][VisualNodeBase] makeConnection connection not permitted");
    }
#endif

    //place the connectors in the right order
    Connector* inputConnector = nullptr;
    Connector* outputConnector = nullptr;
    if(connection->getConnector1()->type == ConnectorType::INPUT)
    {
        inputConnector = connection->getConnector1();
        outputConnector = connection->getConnector2();
    }
    else {
        inputConnector = connection->getConnector2();
        outputConnector = connection->getConnector1();
    }
    OutputNode* outputNode = dynamic_cast<OutputNode*>(outputConnector->getParent()->getNode());
    if(outputNode == nullptr)
    {
        qFatal("[fatal][VisualNodeBase] given output is not a outputnode");
    }
    InputNode* inputNode = dynamic_cast<InputNode*>(inputConnector->getParent()->getNode());
    if(outputNode == nullptr)
    {
        qFatal("[fatal][VisualNodeBase] given input is not a inputNode");
    }

    //make the connection at the low level node
    inputNode->addSubscription(outputNode);

    flowObjects->getHistoricalUpdateManager()->initatiateHistoricalUpdate(inputNode);
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

bool VisualNodeBase::requestConnection(Connector *connector1, Connector* connector2, bool exist)
{
    if(connector1 == connector2)
    {
        return false;
    }
    if(connector1->getParent() != this)
    {
        if(connector2->getParent() != this)
        {
            qFatal("[fatal][VisualNodeBase] request of a connector that is not from this class");
        }
        //connector1 must be connected to this class
        Connector* temp = connector1;
        connector1 = connector2;
        connector2 = temp;
    }
    else {
        if(connector2->getParent() == this)
        {
            //both connectors are connected to this node
            return false;
        }
    }

    if(connector1->type == ConnectorType::OUTPUT)
    {
        if(connector2->type == ConnectorType::OUTPUT)//can't connect output to output
        {
            return false;
        }
        if(connector2->getParent()->recursiveCircularDependencyCheck(this))
        {
            dbgLogger->debug(CLASSNAME,__FUNCTION__,"circular dependency detected on output");
            return false;
        }
    }
    else if(connector1->type == ConnectorType::INPUT)
    {
        if(recursiveCircularDependencyCheck(connector2->getParent()))
        {
           dbgLogger->debug(CLASSNAME,__FUNCTION__,"circular dependency detected on input");
            return false;
        }

        if(connector2->type == ConnectorType::INPUT)//can't connect output to output
        {
            return false;
        }
#ifdef ALLOW_MULTIPLE_INPUT

#else
        if(connector->connections.size() != 0)
        {
            return false;
        }
#endif
    }
    else
    {
        return false;
    }
    //check if the connector is already in the list
    if(!exist)
    {
        //check for double links
        QListIterator<VisualConnection*> iterator(connector1->connections);
        while(iterator.hasNext())
        {
            VisualConnection* currentConnection = iterator.next();
            if(currentConnection->getConnector1() == connector2)
            {
                return false;
            }
            if(currentConnection->getConnector2() == connector2)
            {
                return false;
            }
        }
    }
    return true;
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
                    dbgLogger->error(CLASSNAME,__FUNCTION__,"no input connector");
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

NodeBase *VisualNodeBase::getNode()
{
    return baseNode;
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
                if(requestConnection(connector,(*selectionManager->currentTrackingConnection)->getSetConnector()))//valid connection
                {
                    painter->setBrush(QColor::fromRgbF(0,1,0,0.3));
                }
                else {//invalid connection
                    painter->setBrush(QColor::fromRgbF(1,0,0,0.3));
                }
            }
            painter->drawEllipse(connector->getRect(1.0));


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
    setPos(nodePosition.x(),nodePosition.y());
    QRectF rect = innerRect();

    painter->setPen(nodeStyle->nodeBackgroundColor);
    painter->setBrush(nodeStyle->nodeBackgroundColor);

    painter->drawRoundRect(rect,CONNECTOR_DIAMETER, CONNECTOR_DIAMETER);

    painter->setPen(nodeStyle->nodeCategoryColor);
    painter->setBrush(nodeStyle->nodeCategoryColor);

    QRect titleRect(0,0,width,TITLE_BAR_HEIGHT);
    painter->drawRoundRect(titleRect, 10,10);

    QPen pen;
    if(isSelected())
    {
        pen = QPen(nodeStyle->selectedBorderPen);
    }
    else {
        pen = QPen(nodeStyle->borderPen);
    }
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundRect(rect,CONNECTOR_DIAMETER, CONNECTOR_DIAMETER);


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

    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->getRect(CONNECTOR_MARGINS).contains(event->pos()))
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
    nodePosition += by.toPoint();
}
void VisualNodeBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QListIterator<Connector*> iterator(connectors);
    while(iterator.hasNext())
    {
        Connector* connector = iterator.next();
        if(connector->getRect(CONNECTOR_MARGINS).contains(event->pos()))
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
        if(connector->getRect(CONNECTOR_MARGINS).contains(event->pos()))
        {
            selectionManager->hoveredConnector = connector;
            setToolTip(connector->name);

        }
        else {
            if(selectionManager->hoveredConnector == connector)
            {
                selectionManager->hoveredConnector = nullptr;
            }
            setToolTip(this->name);
        }
    }
}

void VisualNodeBase::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
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

QJsonObject *VisualNodeBase::serializeBase(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert(JSON_BASE_NAME,name);
    jsonObject->insert(JSON_BASE_CENTERX,nodePosition.x());
    jsonObject->insert(JSON_BASE_CENTERY,nodePosition.y());
    jsonObject->insert(JSON_BASE_UNIQUE_ID, getUniqueId());

    return jsonObject;
}
int64_t VisualNodeBase::getUniqueId()
{
    return uniqueId;
}

void VisualNodeBase::deserializeBase(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    name = handler.findStringSafe(CLASSNAME, JSON_BASE_NAME, jsonObject);
    nodePosition.rx() = handler.findIntSafe(CLASSNAME, JSON_BASE_CENTERX, jsonObject);
    nodePosition.ry() = handler.findIntSafe(CLASSNAME, JSON_BASE_CENTERY, jsonObject);
    uniqueId = handler.findInt64Safe(CLASSNAME, JSON_BASE_UNIQUE_ID, jsonObject);
}
