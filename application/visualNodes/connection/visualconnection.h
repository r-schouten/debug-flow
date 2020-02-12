#pragma once

#include "visualnodebase.h"
#include "connector.h"
#include "utils.h"
#include "selectionmanager.h"
#include "connectionstyle.h"
#include "utils.h"

#include "serializable.h"

#include "undoredomanager.h"
class SelectionManager;
class Connector;
class VisualNodeBase;
class VisualConnection: public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit VisualConnection(Connector* connector1);
    explicit VisualConnection(Connector* connector1, Connector* connector2);
    ~VisualConnection();
    void draw(QPainter *painter);
    bool intersect(QPointF position);
    bool connection1Set = false;
    bool connection2Set = false;

    Connector *getConnector1() const;
    Connector *getConnector2() const;
    Connector *getUnsetConnector();
    Connector *getSetConnector();


    void setConnector1(Connector *value);
    void setConnector2(Connector *value);

    void disconnect1();
    void disconnect2();

    void setMousePos(QPoint _mousePos);

    //custom method, this class is not inherited from qgraphicsitem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QJsonObject *serialize(SerializationHandler &handler);

private:
    //begin point and end point
    QPointF point1,point2;

    Connector* connector1 = nullptr;
    Connector* connector2 = nullptr;
    QPoint mousePos;
    SelectionManager* selectionManager = nullptr;
    ConnectionStyle* style = nullptr;
    void makePainterPath();

    //only if anything is changed the painterpath need to be calculated again
    bool settingsChanged = true;
    QPainterPath painterPath;
    PathStyle oldPathStyle;
signals:
    void onDelete(VisualConnection* connection);
};

