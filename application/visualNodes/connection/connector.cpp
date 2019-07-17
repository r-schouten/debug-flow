#include "connector.h"


Connector::Connector(VisualNodeBase *parent, int x, int y, ConnectorType type, int diameter)
    :parent(parent),x(x),y(y),type(type),connectionDiameter(diameter)
{

}
QRectF Connector::getRect(int margins)
{
    margins += connectionDiameter/2;
    return QRectF(x-margins,y-margins,margins*2,margins*2);
}
QPoint Connector::getPoint()
{
    return QPoint(x,y);
}
QPoint Connector::getScenePos()
{
    return QPoint(parent->x() + x ,parent->y() + y);
}
