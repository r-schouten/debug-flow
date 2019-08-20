#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "outputnode.h"
#include "visualnodeconfig.h"
#include "nodebase.h"
#include "nodestylebase.h"
#include "connector.h"
#include "visualconnection.h"
#include "selectionmanager.h"
#include "scenecomponents.h"

class SelectionManager;
class Connector;
class SceneComponents;
class VisualNodeBase : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    VisualNodeBase(SceneComponents *sceneComponents);
    ~VisualNodeBase();

    QString name = "";
    QString shortDiscription = "";
    int centerX = graphicsViewOriginX;
    int centerY = graphicsViewOriginY;
    int width = 100;
    int height = 50;
    QRectF boundingRect() const;
    QRectF innerRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    virtual VisualNodeBase* clone() = 0;

    //easy acces methods for adding the basic connectors, of more needed the can be added to the QList connectors
    void addInputConnector();
    void addOutputConnector();

    void makeConnection(VisualConnection *connection);

    bool requestConnection(Connector *connector);
    bool requestConnection(Connector *connector1, Connector *connector2, bool exist = false);

    void moveBy(QPointF &by);
    bool recursiveCircularDependencyCheck(VisualNodeBase *node);
    virtual void activate() = 0;

    NodeBase* getNode();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void drawConnectors(QPainter *painter, NodeStyleBase *nodeStyle);
    void paintBase(QPainter *painter, NodeStyleBase *nodeStyle, QString name);
    bool isSelected();

    void openSettings();
    //virtual void loadSettings();
    NodeBase* baseNode = nullptr;//each derived class has it own downcasted node pointer

    QList<Connector*> connectors;
    SelectionManager* selectionManager = nullptr;
    SceneComponents* sceneComponents = nullptr;
private:
    bool pressedOnConnection = false;
signals:
    void connectorPressed(VisualNodeBase* node,Connector* connector);
    void connectorReleased(VisualNodeBase* node,Connector* connector);
    void onDelete(VisualNodeBase* node);

};

