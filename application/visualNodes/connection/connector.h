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
    Connector(VisualNodeBase* parent, int x,int y, ConnectorType type, int diameter, double angle, QString name);
    virtual ~Connector();

    QRectF getRect(int margins);
    QPoint getPoint();
    QPoint getScenePos();
    bool connect(VisualConnection *connection);
    void disconnect(VisualConnection* connection);
    VisualNodeBase *getParent();

    bool requestConnector(VisualConnection* connection);
    bool requestConnector(Connector *connector);
    bool requestConnector();

    int x;
    int y;
    double angle;
    QString name;//used for serialization
    ConnectorType type;
    QList<VisualConnection*> connections;
private:
    VisualNodeBase* parent = nullptr;
    int connectionDiameter;
};


