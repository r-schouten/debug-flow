#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "nodebase.h"
#include "nodestylebase.h"
#include "connector.h"
#include "visualconnection.h"
#include "selectionmanager.h"

class SelectionManager;
class Connector;
class VisualNodeBase : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    VisualNodeBase();
    ~VisualNodeBase();

    QString name = "";
    int centerX = 100;
    int centerY = 100;
    const int width = 100;
    const int height = 50;
    QRectF boundingRect() const;
    QRectF innerRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    virtual VisualNodeBase* clone() = 0;

    //easy acces methods for adding the basic connectors, of more needed the can be added to the QList connectors
    void addInputConnector();
    void addOutputConnector();
    bool requestConnection(Connector *connector);
    void moveBy(QPointF &by);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void drawConnectors(QPainter *painter);
    void paintBase(QPainter *painter, NodeStyleBase *nodeStyle, QString name);
    bool isSelected();

    QList<Connector*> connectors;
    SelectionManager* selectionManager;
signals:
    void connectorPressed(VisualNodeBase* node,Connector* connector);
    void connectorReleased(VisualNodeBase* node,Connector* connector);
    void onDelete(VisualNodeBase* node);
};

