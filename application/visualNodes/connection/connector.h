#pragma once
#include <QPoint>
#include <QRectF>
#include "visualconnection.h"

class VisualNodeBase;
class VisualConnection;
enum class ConnectorType
{
    INPUT,
    OUTPUT
};
class Connector
{
public:
    Connector(VisualNodeBase* parent, int x,int y, ConnectorType type, int diameter);
    QRectF getRect(int margins);
    QPoint getPoint();
    QPoint getScenePos();

    int x;
    int y;
    ConnectorType type;
    QList<VisualConnection*> connections;
private:
    int connectionDiameter = 10;
    VisualNodeBase* parent = nullptr;
};


