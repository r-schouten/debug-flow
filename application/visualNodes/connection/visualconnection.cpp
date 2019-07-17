#include "visualconnection.h"

VisualConnection::VisualConnection(Connector *connector1)
    :connector1(connector1)
{
    connection1Set = true;
}

VisualConnection::VisualConnection(Connector *connector1, Connector *connector2)
    :connector1(connector1),connector2(connector2)
{
    connection1Set = true;
    connection2Set = true;
}

void VisualConnection::draw(QPainter* painter)
{
    painter->setBrush(QColor::fromRgbF(1,1,1,0.7));
    QPen pen(QColor::fromRgbF(1,1,1,0.7));
    pen.setWidth(10);
    painter->setPen(pen);

    QPoint point1,point2;
    if(connection1Set)
    {
        point1 = connector1->getScenePos();
    }
    else {
        point1 = mousePos;
    }
    if(connection2Set)
    {
        point2 = connector2->getScenePos();
    }
    else {
        point2 = mousePos;
    }
    painter->drawLine(point1,point2);
}

void VisualConnection::setMousePos(QPoint _mousePos)
{
    mousePos = _mousePos;
}

void VisualConnection::disconnect1()
{
    connector1 = nullptr;
    connection1Set = false;
}
Connector *VisualConnection::getConnector1() const
{
    return connector1;
}

void VisualConnection::setConnector1(Connector *value)
{
    connector1 = value;
    connection1Set = true;
}

void VisualConnection::disconnect2()
{
    connector2 = nullptr;
    connection2Set = false;
}


Connector *VisualConnection::getConnector2() const
{
    return connector2;
}

void VisualConnection::setConnector2(Connector *value)
{
    connector2 = value;
    connection2Set = true;
}
