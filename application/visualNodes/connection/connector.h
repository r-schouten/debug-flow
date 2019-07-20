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
    Connector(VisualNodeBase* parent, int x,int y, ConnectorType type, int diameter, double angle);
    ~Connector();

    QRectF getRect(int margins);
    QPoint getPoint();
    QPoint getScenePos();
    bool connect(VisualConnection *connection);
    void disconnect(VisualConnection* connection);
    VisualNodeBase *getParent();

    bool requestConnector(VisualConnection* connection);
    int x;
    int y;
    double angle;
    ConnectorType type;
    QList<VisualConnection*> connections;
private:
    int connectionDiameter = 10;
    VisualNodeBase* parent = nullptr;
};


