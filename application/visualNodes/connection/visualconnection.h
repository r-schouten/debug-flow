#pragma once

#include "visualnodebase.h"
#include "connector.h"
class Connector;
class VisualNodeBase;
class VisualConnection
{
public:
    explicit VisualConnection(Connector* connector1);
    explicit VisualConnection(Connector* connector1, Connector* connector2);
    void draw(QPainter *painter);
    bool connection1Set = false;
    bool connection2Set = false;

    Connector *getConnector1() const;
    void setConnector1(Connector *value);
    void disconnect1();

    Connector *getConnector2() const;
    void setConnector2(Connector *value);
    void disconnect2();

    void setMousePos(QPoint _mousePos);
private:
    Connector* connector1 = nullptr;
    Connector* connector2 = nullptr;
    QPoint mousePos;

};

