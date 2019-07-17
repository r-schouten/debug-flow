#pragma once
#include <QGraphicsScene>
#include <QPainter>
#include "visualnodebase.h"
#include "utils.h"
class NodeScene:public QGraphicsScene
{
    Q_OBJECT
public:
    NodeScene();

    void insertItem(VisualNodeBase* node);
    void addItem(VisualNodeBase *item);
public slots:
    void connectorPressed(VisualNodeBase *node, Connector *connector);
    void connectorReleased(VisualNodeBase *node, Connector *connector);
private:
    void drawGrid(QPainter *painter, const QRectF &rect, int gridSize, QPen *pen);
    VisualNodeBase* nodeToPlace = nullptr;
    enum class NodePlacementState
    {
        NOT_PLACING,
        PLACE_AFTER_CLICK
    }nodePlacementState = NodePlacementState::NOT_PLACING;
    bool anyConnectorPressed = false;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &rect);
private:
    QList<VisualConnection*> connections;
    QList<VisualNodeBase*> nodes;
    VisualConnection* currentTrackingConnection = nullptr;
};

