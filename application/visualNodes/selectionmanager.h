#pragma once
#include "visualnodebase.h"
#include "visualconnection.h"
#include "scenecomponents.h"

class SceneComponents;
class Connector;
class VisualNodeBase;
class VisualConnection;
class SelectionManager
{
private:
    bool hadUpdate = false;
public:
    SelectionManager(SceneComponents *sceneComponents);
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
