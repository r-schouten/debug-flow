#pragma once
#include "visualnodebase.h"
#include "visualconnection.h"

class Connector;
class VisualNodeBase;
class VisualConnection;

//note this class is a singleton!
class SelectionManager
{
private:
    SelectionManager(){}
    static SelectionManager* singletonSelectionManger;

    bool hadUpdate = false;
public:
    static SelectionManager* getInstance();
    bool isSelected(VisualNodeBase *node);
    bool isSelected(VisualConnection *connection);

    void setSelected(VisualNodeBase* node, bool clear = true);
    void setSelected(VisualConnection* connection, bool clear = true);

    void clearSelected();

    bool isUpdated();
    void clearUpdateFlag();

    QList<VisualNodeBase*> selectedNodes;
    QList<VisualConnection*> selectedConnections;
    Connector* hoveredConnector = nullptr;
    VisualConnection** currentTrackingConnection = nullptr;
};
