#include "connector.h"

#include <nodeInput.h>


Connector::Connector(VisualNodeBase *parent, int x, int y, ConnectorType type, int diameter, double angle, QString name)
    :parent(parent),x(x),y(y),type(type),connectionDiameter(diameter),angle(angle), name(name)
{

}

Connector::~Connector()
{
    QListIterator<VisualConnection*> iterator(connections);
    while(iterator.hasNext())
    {
        delete iterator.next();
    }
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
bool Connector::connect(VisualConnection *connection)
{
    connections.append(connection);
    return true;
}
void Connector::disconnect(VisualConnection *connection)
{
    if(connections.contains(connection))
    {
        if(connection->connection1Set && connection->connection2Set)
        {
            Connector* inputConnector = nullptr;
            Connector* outputConnector = nullptr;
            if(connection->getConnector1()->type == ConnectorType::INPUT)
            {
                inputConnector = connection->getConnector1();
                outputConnector = connection->getConnector2();
            }
            else {
                inputConnector = connection->getConnector2();
                outputConnector = connection->getConnector1();
            }
            NodeInput* inputNode = inputConnector->getParent()->getNode()->getInput(0);
            NodeOutput* outputNode = outputConnector->getParent()->getNode()->getOutput(0);
            if((inputNode) && (outputNode))
            {
                inputNode->deleteSubscription(outputNode);
            }
            else
            {
                parent->dbgLogger->error("Connector", __FUNCTION__,"can't cast to input node or ouput node");
            }
        }
        if(connections.removeOne(connection))
        {

        }
        else {
            parent->dbgLogger->error("Connector", __FUNCTION__,"remove connection failed");
        }
    }
    else {
        parent->dbgLogger->error("Connector", __FUNCTION__,"disconnect failed connection not in connections");
    }
}

VisualNodeBase *Connector::getParent()
{
#ifdef QT_DEBUG
    if(parent == nullptr)
    {
        parent->dbgLogger->fatal("Connector", __FUNCTION__,"parent is nullptr");
    }
#endif
    return parent;
#
}
bool Connector::requestConnector()
{
    return parent->requestConnection(this);
}

bool Connector::requestConnector(VisualConnection *connection)
{
    return parent->requestConnection(this,connection->getSetConnector());
}
bool Connector::requestConnector(Connector* connector)
{
    return parent->requestConnection(this, connector);
}
