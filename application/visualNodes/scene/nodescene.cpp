#include "nodescene.h"


NodeScene::NodeScene()
{
    QBrush brush(QColor::fromRgb(100, 100, 100));
    setBackgroundBrush(brush);
}
//this methode takes the ownership over
void NodeScene::insertItem(VisualNodeBase *node)
{
    addItem(node);
    node->setVisible(false);
    nodeToPlace = node;
    nodePlacementState = NodePlacementState::PLACE_AFTER_CLICK;
}

void NodeScene::addItem(VisualNodeBase *item)
{
    connect(item,SIGNAL(connectorPressed(VisualNodeBase*,Connector*)),this,SLOT(connectorPressed(VisualNodeBase*,Connector*)));
    connect(item,SIGNAL(connectorReleased(VisualNodeBase*,Connector*)),this,SLOT(connectorReleased(VisualNodeBase*,Connector*)));

    nodes.append(item);
    QGraphicsScene::addItem(item);
}
void NodeScene::connectorPressed(VisualNodeBase* node,Connector* connector)
{
    qDebug("[debug][NodeScene] connectorPressed");
    anyConnectorPressed = true;

    if(currentTrackingConnection)
    {
        return;
    }
    qDebug("[debug][NodeScene] connector clicked");
    if(connector->type == ConnectorType::INPUT)
    {
        if(!node->requestConnection(connector))
        {
            qDebug("[debug][NodeScene] type = input, request not accepted");
            return;
        }
    }

    VisualConnection* newConnection = new VisualConnection(connector);
    connections.append(newConnection);
    currentTrackingConnection = newConnection;
}
void NodeScene::connectorReleased(VisualNodeBase* node,Connector* connector)
{
    if(currentTrackingConnection == nullptr)
    {
        return;
    }
    if(currentTrackingConnection->getConnector1() == connector)
    {
        qDebug("[debug][NodeScene] connector1 == connector");
    }
    else if(currentTrackingConnection->getConnector2() == connector)
    {
        qDebug("[debug][NodeScene] connector2 == connector");
    }
    else {
        if(!currentTrackingConnection->connection1Set)
        {
            currentTrackingConnection->setConnector1(connector);
            currentTrackingConnection = nullptr;
        }
        else if(!currentTrackingConnection->connection2Set)
        {
            currentTrackingConnection->setConnector2(connector);
            currentTrackingConnection = nullptr;
        }

    }

}

void NodeScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QListIterator<VisualConnection*>iterator(connections);
    while(iterator.hasNext())
    {
        VisualConnection* connection = iterator.next();
        connection->draw(painter);
    }
}
void NodeScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);

    QPen pen;

    pen.setColor(QColor::fromRgb(110, 110, 110));
    drawGrid(painter,rect,10,&pen);

    pen.setColor(QColor::fromRgb(125, 125, 125));
    drawGrid(painter,rect,50,&pen);

}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(nodePlacementState != NodePlacementState::NOT_PLACING)
    {
            nodeToPlace->setVisible(true);
            nodeToPlace->centerX = event->scenePos().x();
            nodeToPlace->centerY = event->scenePos().y();
    }
    if(currentTrackingConnection)
    {
        currentTrackingConnection->setMousePos(event->scenePos().toPoint());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("[debug][NodeScene] mousepress");

    if(nodePlacementState == NodePlacementState::PLACE_AFTER_CLICK)
    {
        nodePlacementState = NodePlacementState::NOT_PLACING;
        nodeToPlace = nullptr;
    }
    QGraphicsScene::mousePressEvent(event);
    //after the super call all the childeren are checked
    qDebug("[debug][NodeScene] mousepress done");

    if(!anyConnectorPressed)
    {
        currentTrackingConnection = nullptr;
    }

    anyConnectorPressed = false;

}
void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(currentTrackingConnection)
    {
        QListIterator<VisualNodeBase*>iterator(nodes);
        while(iterator.hasNext())
        {
            VisualNodeBase* node = iterator.next();

        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
void NodeScene::drawGrid(QPainter * painter, const QRectF &rect, int gridSize, QPen* pen)
{
    int left = rect.left() - (int(rect.left()) % gridSize);
    int top = rect.top() - (int(rect.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (int x = left; x < rect.right(); x += gridSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (int y = top; y < rect.bottom(); y += gridSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->setPen(*pen);
    painter->drawLines(lines.data(), lines.size());
}
