#pragma once
#include "propertywidgetmanager.h"

class Connector;
class VisualNodeBase;
class VisualConnection;
class PropertyWidgetManager;
//note this class is a singleton!
class   SelectionManager
{
private:
    SelectionManager(){}
    static SelectionManager singletonSelectionManger;

    bool hadUpdate = false;

    PropertyWidgetManager* propertyWidgetManager = nullptr;
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
    void setPropertyWidgetManager(PropertyWidgetManager *value);
    void removeOne(VisualNodeBase *node);
};
