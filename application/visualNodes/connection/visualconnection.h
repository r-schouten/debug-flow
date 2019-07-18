#pragma once

#include "visualnodebase.h"
#include "connector.h"
#include "utils.h"
class Connector;
class VisualNodeBase;
class VisualConnection: public QObject
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

    void setConnector1(Connector *value);
    void setConnector2(Connector *value);

    void disconnect1();
    void disconnect2();

    void setMousePos(QPoint _mousePos);
private:
    Connector* connector1 = nullptr;
    Connector* connector2 = nullptr;
    QPoint mousePos;
signals:
    void onDelete(VisualConnection* connection);
};

