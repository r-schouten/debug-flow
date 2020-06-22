#pragma once
#include "propertywidgetmanager.h"
#include "dbglogger.h"
class Connector;
class VisualNodeBase;
class VisualConnection;
class PropertyWidgetManager;

class SelectionManager
{
private:
    bool hadUpdate = false;

    PropertyWidgetManager* propertyWidgetManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
public:
    SelectionManager(PropertyWidgetManager *_propertyWidgetManager, DbgLogger* dbgLogger);
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
    void removeOne(VisualNodeBase *node);
};
