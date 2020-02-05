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

#include "flowdata.h"
#include "serializable.h"
class NodeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    NodeScene(FlowData* _flowData);

    //function to insert items from the resource list
    void insertItem(VisualNodeBase* node);
    void addItem(VisualNodeBase *item);

private:
    FlowData* flowData = nullptr;

    //flag for adding connections
    bool anyConnectorPressed = false;

    //connection that is tracked by the mouse, set back to nullptr
    VisualConnection* currentTrackingConnection = nullptr;

    //selectionmanager singleton
    SelectionManager* selectionManager;

    //if true selected nodes will follow the mouse movement
    bool moveSelected = false;
    QPointF lastMousePosition;

    //when a new node is inserted from the resource list its hold by nodeToPlace
    //set it back to nullptr
    VisualNodeBase* nodeToPlace = nullptr;
    enum class NodePlacementState
    {
        NOT_PLACING,
        PLACE_AFTER_CLICK
    }nodePlacementState = NodePlacementState::NOT_PLACING;

    //background
    void drawGrid(QPainter *painter, const QRectF &rect, int gridSize, QPen *pen);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    //draw all connections
    void drawForeground(QPainter *painter, const QRectF &rect);
public slots:
    //slots for visualnode communication
    void connectorPressed(VisualNodeBase *node, Connector *connector);
    void connectorReleased(VisualNodeBase *node, Connector *connector);

    //slot for visualConnector communication
    void onConnectionDelete(VisualConnection *connection);
    void onNodeDelete(VisualNodeBase *node);
};

