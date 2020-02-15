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
#include "propertieswidgetnoneselected.h"

#include "serializable.h"
#include "json_defs.h"
#include "serialization_handler.h"
#include "deserialization_handler.h"

#include "movecommand.h"

class SelectionManager;
class Connector;
class VisualNodeBase : public QObject, public QGraphicsItem, public Serializable
{
    Q_OBJECT
public:
    VisualNodeBase();
    VisualNodeBase(QJsonObject &jsonObject, DeserializationHandler &handler);
    ~VisualNodeBase();

    //will be filled in by the derived class
    QString name = "";
    QString shortDiscription = "";

    //position on the scene
    QPoint nodePosition;
    //used for undo
    QPoint oldPosition;
    int width = 125;
    int height = 50;


    //size including connectors
    QRectF boundingRect() const;
    //size of the rectangle
    QRectF innerRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    //this function is used to copy a node from the resource list. Its implemented in the derived class so a upcasted type will be returned
    virtual VisualNodeBase* clone() = 0;

    Connector *findConnectorWithName(QString name);

    //makes the connection (definitive) in the low level VisualBase object, (run requestConnection and recursiveCircularDependencyCheck first)
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

    QJsonObject* serializeBase(SerializationHandler &handler);
    void deserializeBase(QJsonObject &jsonObject, DeserializationHandler &handler);

    //the unique id is used to connect nodes and connectors when deserializing
    int64_t getUniqueId();

protected:
    //the current open property widget
    PropertyWidgetBase* propertyWidget = nullptr;

    //each derived class has it own downcasted node pointer
    NodeBase* baseNode = nullptr;

    QList<Connector*> connectors;
    //note that selection manager is a singleton
    SelectionManager* selectionManager = nullptr;

    //the unique id is used to connect nodes and connectors when deserializing
    int64_t uniqueId = 0;

    //easy access methods for adding the basic connectors at setup, of more needed the can be added to the QList connectors
    void addInputConnector();
    void addOutputConnector();

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

