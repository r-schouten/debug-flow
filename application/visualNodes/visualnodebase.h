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
#include "propertywidgetbase.h"

#include "serializable.h"
#include "json_defs.h"
#include "serialization_settings.h"
#include "serialization_handler.h"
class SelectionManager;
class Connector;
class VisualNodeBase : public QObject, public QGraphicsItem, public Serializable
{
    Q_OBJECT
public:
    VisualNodeBase();
    VisualNodeBase(QJsonObject &jsonObject, SerializationHandler &handler);
    ~VisualNodeBase();

    //will be filled in by the derived class
    QString name = "";
    QString shortDiscription = "";

    //position on the scene
    int centerX = graphicsViewOriginX;
    int centerY = graphicsViewOriginY;
    int width = 125;
    int height = 50;

    QRectF boundingRect() const;
    QRectF innerRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    //this function is used to copy a node from the resource list. Its implemented in the derived class so a upcasted type will be returned
    virtual VisualNodeBase* clone() = 0;

    //easy acces methods for adding the basic connectors, of more needed the can be added to the QList connectors
    void addInputConnector();
    void addOutputConnector();

    //makes the connection in the low level VisualBase object, (run requestConnection and recursiveCircularDependencyCheck first)
    void makeConnection(VisualConnection *connection);

    //check if the connection is possible
    bool requestConnection(Connector *connector);
    bool requestConnection(Connector *connector1, Connector *connector2, bool exist = false);

    //checks if there is no infinity loop made
    bool recursiveCircularDependencyCheck(VisualNodeBase *node);

    void moveBy(QPointF &by);

    //activate the derived class
    virtual void activate() = 0;

    NodeBase* getNode();

    virtual PropertyWidgetBase* loadPropertiesWidget(QWidget* parent) = 0;
    virtual void releasePropertiesWidget() = 0;

    QJsonObject* serializeBase(SerializationSettings_t &serialisationSettings, SerializationHandler &serialisationErrorLog);
    void deserializeBase(QJsonObject &jsonObject, SerializationHandler &handler);
protected:
    PropertyWidgetBase* propertyWidget = nullptr;

    NodeBase* baseNode = nullptr;//each derived class has it own downcasted node pointer

    QList<Connector*> connectors;
    //note that selection manager is a singleton
    SelectionManager* selectionManager = nullptr;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void drawConnectors(QPainter *painter, NodeStyleBase *nodeStyle);
    void paintBase(QPainter *painter, NodeStyleBase *nodeStyle, QString name);
    bool isSelected();

private:
    bool pressedOnConnection = false;
signals:
    void connectorPressed(VisualNodeBase* node,Connector* connector);
    void connectorReleased(VisualNodeBase* node,Connector* connector);
    void onDelete(VisualNodeBase* node);

};

