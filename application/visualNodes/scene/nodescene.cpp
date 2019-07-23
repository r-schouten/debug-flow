#include "nodescene.h"

#include <qevent.h>
#include <visualoutputnodebase.h>


NodeScene::NodeScene(WindowManager* windowManager)
    :windowManager(windowManager)
{
    selectionManager = SelectionManager::getInstance();
    QBrush brush(QColor::fromRgb(100, 100, 100));
    setBackgroundBrush(brush);
    selectionManager->currentTrackingConnection = &currentTrackingConnection;
    setItemIndexMethod(NoIndex);


}
//this methode takes the ownership over
void NodeScene::insertItem(VisualNodeBase *node)
{
    if(nodeToPlace)//already placing a node
    {
        delete nodeToPlace;
    }
    addItem(node);
    node->setVisible(false);
    nodeToPlace = node;
    nodePlacementState = NodePlacementState::PLACE_AFTER_CLICK;
    selectionManager->setSelected(nodeToPlace, true);
}

void NodeScene::addItem(VisualNodeBase *item)
{
    connect(item,SIGNAL(connectorPressed(VisualNodeBase*,Connector*)),this,SLOT(connectorPressed(VisualNodeBase*,Connector*)));
    connect(item,SIGNAL(connectorReleased(VisualNodeBase*,Connector*)),this,SLOT(connectorReleased(VisualNodeBase*,Connector*)));
    connect(item,SIGNAL(onDelete(VisualNodeBase*)),this,SLOT(onNodeDelete(VisualNodeBase*)));

    if(dynamic_cast<VisualOutputNodeBase*>(item))
    {
        dynamic_cast<VisualOutputNodeBase*>(item)->setWindowManager(windowManager);
    }
    item->activate();
    nodes.append(item);
    QGraphicsScene::addItem(item);
}
void NodeScene::connectorPressed(VisualNodeBase* node,Connector* connector)
{
    //qDebug("[debug][NodeScene] connectorPressed");
    anyConnectorPressed = true;

    if(currentTrackingConnection)
    {
        return;
    }
    //qDebug("[debug][NodeScene] connector clicked");
    if(connector->type == ConnectorType::INPUT)
    {
        if(!connector->requestConnector())
        {
            qDebug("[debug][NodeScene] type = input, request not accepted");
            return;
        }
    }
    selectionManager->clearSelected();
    VisualConnection* newConnection = new VisualConnection(connector);
    connections.append(newConnection);
    currentTrackingConnection = newConnection;
    connect(newConnection,SIGNAL(onDelete(VisualConnection*)),this,SLOT(onConnectionDelete(VisualConnection*)));
}
void NodeScene::connectorReleased(VisualNodeBase* node,Connector* connector)
{
    //qDebug("[debug][NodeScene] connectorReleased");

    if(currentTrackingConnection == nullptr)
    {
        return;
    }
    if(!connector->requestConnector(currentTrackingConnection))
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
            node->makeConnection(currentTrackingConnection);
            currentTrackingConnection = nullptr;
        }
        else if(!currentTrackingConnection->connection2Set)
        {
            currentTrackingConnection->setConnector2(connector);
            node->makeConnection(currentTrackingConnection);
            currentTrackingConnection = nullptr;
        }
    }

}
void NodeScene::onNodeDelete(VisualNodeBase* node)
{
    removeItem(node);
    selectionManager->selectedNodes.removeOne(node);
    if(nodes.removeOne(node))
    {

    }
    else {
        qDebug("[error,NodeScene] failed to remove node");
    }
    if(nodeToPlace == node)
    {
        nodeToPlace = nullptr;
        nodePlacementState = NodePlacementState::NOT_PLACING;
    }
}
void NodeScene::onConnectionDelete(VisualConnection* connection)
{
    if(connections.removeOne(connection))
    {

    }
    else {
        qDebug("[error,NodeScene] failed to remove connection");
    }
    if(currentTrackingConnection == connection)
    {
        currentTrackingConnection = nullptr;
    }
}


void NodeScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);

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
        //note the use of side effects here
        if((selectionManager->hoveredConnector == nullptr)||(!selectionManager->hoveredConnector->requestConnector(currentTrackingConnection)))
        {
            currentTrackingConnection->setMousePos(event->scenePos().toPoint());
        }
        else
        {
            //snapping to the connector
            currentTrackingConnection->setMousePos(selectionManager->hoveredConnector->getScenePos());
        }
    }
    if(moveSelected)
    {
        QPointF mouseMovement = event->scenePos() - lastMousePosition;
        QListIterator<VisualNodeBase*>iterator(selectionManager->selectedNodes);
        while(iterator.hasNext())
        {
            VisualNodeBase* node = iterator.next();
            node->moveBy(mouseMovement);
        }
        lastMousePosition = event->scenePos();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("[debug][NodeScene] mousepress");

    //for placement of a new object
    if(nodePlacementState == NodePlacementState::PLACE_AFTER_CLICK)
    {
        nodePlacementState = NodePlacementState::NOT_PLACING;
        nodeToPlace = nullptr;
    }

    QGraphicsScene::mousePressEvent(event);
    //after the super call all the childeren are checked

    //qDebug("[debug][NodeScene] mousepress done");

    //for connecting a connector to a node

    //if no node is clicked
    if(!anyConnectorPressed)
    {
        if(currentTrackingConnection!=nullptr)
        {
            delete currentTrackingConnection;
            currentTrackingConnection = nullptr;
        }
        if(currentTrackingConnection == nullptr)
        {
            QListIterator<VisualConnection*>iterator(connections);
            while(iterator.hasNext())
            {
                VisualConnection* currentConnection = iterator.next();
                currentConnection->mousePressEvent(event);
            }
        }
        if(selectionManager->isUpdated())
        {
            moveSelected = true;
            lastMousePosition = event->scenePos();
        }
        else
        {
            selectionManager->clearSelected();
        }
    }
    selectionManager->clearUpdateFlag();
    anyConnectorPressed = false;

}
void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    moveSelected = false;
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

void NodeScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QListIterator<VisualConnection*>iterator(selectionManager->selectedConnections);
        while(iterator.hasNext())
        {
            VisualConnection* connection = iterator.next();
            //connection will delete notify its dependend objects
            delete connection;
        }
        QListIterator<VisualNodeBase*>iterator2(selectionManager->selectedNodes);
        while(iterator2.hasNext())
        {
            VisualNodeBase* node = iterator2.next();
            //node will notify depended objects(include nodeScene)
            delete node;
        }
        selectionManager->clearSelected();
    }
    if ((event->key() == Qt::Key_Escape)||(event->key() == Qt::Key_Delete))
    {
        selectionManager->clearSelected();
        if(currentTrackingConnection)
        {
            delete currentTrackingConnection;
            currentTrackingConnection = nullptr;
        }
    }
}
