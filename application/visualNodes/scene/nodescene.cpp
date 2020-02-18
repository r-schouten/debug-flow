#include "nodescene.h"

NodeScene::NodeScene(FlowData *_flowData, UndoRedoManager* _undoRedoManager)
    :flowData(_flowData), undoRedoManager(_undoRedoManager)
{
    selectionManager = SelectionManager::getInstance();

    QBrush brush(QColor::fromRgb(100, 100, 100));
    setBackgroundBrush(brush);

    selectionManager->currentTrackingConnection = &currentTrackingConnection;

    //no indexing but faster drawing
    setItemIndexMethod(NoIndex);

}

//this method takes the ownership over
void NodeScene::insertNode(VisualNodeBase *node)
{
    if(nodeToPlace)//already placing a node
    {
        delete nodeToPlace;
    }
    addNode(node);
    node->setVisible(false);
    nodeToPlace = node;
    nodePlacementState = NodePlacementState::PLACE_AFTER_CLICK;
    selectionManager->setSelected(nodeToPlace, true);

    //make a undo redo event
    undoRedoManager->registerEvent();
    undoRedoManager->pushChange(new NodeCommand(node, NodeCommand::CREATE));
}

void NodeScene::addNode(VisualNodeBase *item)
{
    connect(item,SIGNAL(connectorPressed(VisualNodeBase*,Connector*)),this,SLOT(connectorPressed(VisualNodeBase*,Connector*)));
    connect(item,SIGNAL(connectorReleased(VisualNodeBase*,Connector*)),this,SLOT(connectorReleased(VisualNodeBase*,Connector*)));
    connect(item,SIGNAL(onDelete(VisualNodeBase*)),this,SLOT(onNodeDelete(VisualNodeBase*)));

    if(dynamic_cast<VisualOutputNodeBase*>(item))
    {
        dynamic_cast<VisualOutputNodeBase*>(item)->setWindowManager(flowData->windowManager);
    }
    item->activate();
    flowData->nodes.append(item);
    QGraphicsScene::addItem(item);
}
void NodeScene::addConnection(VisualConnection* newConnection)
{
    flowData->connections.append(newConnection);
    connect(newConnection,SIGNAL(onDelete(VisualConnection*)),this,SLOT(onConnectionDelete(VisualConnection*)));
    if((newConnection->connection1Set) && (newConnection->connection2Set))
    {
        newConnection->getConnector1()->getParent()->makeConnection(newConnection);
    }
}

void NodeScene::onNodeDelete(VisualNodeBase* node)
{
    removeItem(node);
    selectionManager->removeOne(node);
    if(flowData->nodes.removeOne(node))
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
    if(connection->deleteReason == VisualConnection::DeleteReason::NORMAL)
    {
        if(connection->connection1Set && connection->connection2Set)
        {
            undoRedoManager->pushChange(new ConnectionCommand(connection,ConnectionCommand::DELETE));
        }
    }

    if(flowData->connections.removeOne(connection))
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
    Q_UNUSED(rect);
    painter->setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);

    QListIterator<VisualConnection*>iterator(flowData->connections);
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

void NodeScene::connectorPressed(VisualNodeBase* node,Connector* connector)
{
    Q_UNUSED(node);
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
    addConnection(newConnection);
    currentTrackingConnection = newConnection;
    currentTrackingConnection->setMousePos(lastMousePosition.toPoint());
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
            //connect the connection object to the connector
            currentTrackingConnection->setConnector1(connector);
            //make the low level connection between the nodes for data interaction
            node->makeConnection(currentTrackingConnection);

            //push undo point
            ConnectionCommand* connectionCommand = new ConnectionCommand(currentTrackingConnection, ConnectionCommand::CREATE);
            undoRedoManager->pushChange(connectionCommand);

            //don't track anymore
            currentTrackingConnection = nullptr;
        }
        else if(!currentTrackingConnection->connection2Set)
        {
            //connect the connection object to the connector
            currentTrackingConnection->setConnector2(connector);
            //make the low level connection between the nodes for data interaction
            node->makeConnection(currentTrackingConnection);

            //push undo point
            ConnectionCommand* connectionCommand = new ConnectionCommand(currentTrackingConnection, ConnectionCommand::CREATE);
            undoRedoManager->pushChange(connectionCommand);

            //don't track anymore
            currentTrackingConnection = nullptr;
        }
    }
}


void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(nodePlacementState != NodePlacementState::NOT_PLACING)
    {
            nodeToPlace->setVisible(true);
            nodeToPlace->nodePosition = event->scenePos().toPoint();
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

    }
    lastMousePosition = event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //make a undo redo event
    undoRedoManager->registerEvent();
    //qDebug("[debug][NodeScene] mousepress");

    QGraphicsScene::mousePressEvent(event);
    //after the super class call all the childeren are checked

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
            QListIterator<VisualConnection*>iterator(flowData->connections);
            while(iterator.hasNext())
            {
                VisualConnection* currentConnection = iterator.next();
                currentConnection->mousePressEvent(event);
            }
        }
        if(selectionManager->isUpdated())
        {
            moveSelected = true;
            QListIterator<VisualNodeBase*>iterator(selectionManager->selectedNodes);
            while(iterator.hasNext())
            {
                VisualNodeBase* node = iterator.next();
                node->oldPosition = node->nodePosition;
            }
            lastMousePosition = event->scenePos();
        }
        else
        {
            selectionManager->clearSelected();
        }
    }
    selectionManager->clearUpdateFlag();
    anyConnectorPressed = false;

    //for placement of a new object
    if(nodePlacementState == NodePlacementState::PLACE_AFTER_CLICK)
    {
        nodePlacementState = NodePlacementState::NOT_PLACING;
        nodeToPlace = nullptr;
        moveSelected = false;
    }

}
void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //make a undo redo event
    undoRedoManager->registerEvent();
    if(moveSelected)
    {
        QListIterator<VisualNodeBase*>iterator(selectionManager->selectedNodes);
        while(iterator.hasNext())
        {
            VisualNodeBase* node = iterator.next();
            if(node->oldPosition != node->nodePosition)
            {
                //save this change to the undo stack
                undoRedoManager->pushChange(new MoveCommand(node,node->oldPosition, node->nodePosition));
            }
        }
        moveSelected = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void NodeScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        //make a undo redo event
        undoRedoManager->registerEvent();

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

            CommandBase* command = new NodeCommand(node, NodeCommand::DELETE);

            delete node;

            //when deleting a node the connected connection will also be deleted. first the connection need to be added to the undo stack and after that the node should be added, therefore this order.
            undoRedoManager->pushChange(command);
        }
        selectionManager->clearSelected();
    }
    if ((event->key() == Qt::Key_Escape)||(event->key() == Qt::Key_Delete))
    {
        //make a undo redo event
        undoRedoManager->registerEvent();

        selectionManager->clearSelected();
        if(currentTrackingConnection)
        {
            delete currentTrackingConnection;
            currentTrackingConnection = nullptr;
        }
    }

}
