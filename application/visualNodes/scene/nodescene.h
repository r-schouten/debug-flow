#pragma once
#include <QGraphicsScene>
#include <windowmanager.h>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <qevent.h>
#include <QPainter>

#include "visualoutputnodebase.h"
#include "visualnodebase.h"
#include "utils.h"
#include "selectionmanager.h"
#include "outputstyle.h"

#include "serializable.h"
class NodeScene : public QGraphicsScene, public Serializable
{
    Q_OBJECT
public:
    NodeScene(WindowManager *windowManager);

    //function to insert items from the resource list
    void insertItem(VisualNodeBase* node);
    void addItem(VisualNodeBase *item);

    QJsonObject* serialize();
    void deserialize(QJsonObject* jsonObject);
public slots:
    //slots for visualnode communication
    void connectorPressed(VisualNodeBase *node, Connector *connector);
    void connectorReleased(VisualNodeBase *node, Connector *connector);

    //slot for visualConnector communication
    void onConnectionDelete(VisualConnection *connection);
    void onNodeDelete(VisualNodeBase *node);
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

    WindowManager* windowManager = nullptr;
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
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    //draw all connections
    void drawForeground(QPainter *painter, const QRectF &rect);


};

