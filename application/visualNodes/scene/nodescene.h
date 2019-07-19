#pragma once
#include <QGraphicsScene>

#include <QPainter>
#include "visualnodebase.h"
#include "utils.h"
#include "selectionmanager.h"
class NodeScene:public QGraphicsScene
{
    Q_OBJECT
public:
    NodeScene();

    //function to insert items from the resource list
    void insertItem(VisualNodeBase* node);
    void addItem(VisualNodeBase *item);
public slots:
    //slots for visualnode communication
    void connectorPressed(VisualNodeBase *node, Connector *connector);
    void connectorReleased(VisualNodeBase *node, Connector *connector);
    //slot for visualConnector communication
    void onConnectionDelete(VisualConnection *connection);
private:
    //background
    void drawGrid(QPainter *painter, const QRectF &rect, int gridSize, QPen *pen);

    //when a new node is inserted from the resource list its hold by nodeToPlace
    //set it back to nullptr
    VisualNodeBase* nodeToPlace = nullptr;
    enum class NodePlacementState
    {
        NOT_PLACING,
        PLACE_AFTER_CLICK
    }nodePlacementState = NodePlacementState::NOT_PLACING;

    //flag for adding connections
    bool anyConnectorPressed = false;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //draw all connections
    void drawForeground(QPainter *painter, const QRectF &rect);
private:
    //hold all connections, they are not graphics items
    QList<VisualConnection*> connections;
    //connection that is tracked by the mouse, set back to nullptr
    VisualConnection* currentTrackingConnection = nullptr;

    //list with all nodes
    QList<VisualNodeBase*> nodes;

    //selectionmanager singleton
    SelectionManager* selectionManager;

    //if true selected nodes will move with the mouse
    bool moveSelected = false;
    QPointF lastMousePosition;
};

