#include "selectionmanager.h"

SelectionManager::SelectionManager(PropertyWidgetManager *_propertyWidgetManager, DbgLogger *dbgLogger)
    :propertyWidgetManager(_propertyWidgetManager),dbgLogger(dbgLogger)
{

}



bool SelectionManager::isSelected(VisualNodeBase* node)
{
    return selectedNodes.contains(node);
}
bool SelectionManager::isSelected(VisualConnection* connection)
{
    return selectedConnections.contains(connection);
}
void SelectionManager::setSelected(VisualNodeBase *node, bool clear)
{
    if(clear)
    {
        selectedNodes.clear();
        selectedConnections.clear();
    }
    if(!selectedNodes.contains(node))
    {
        selectedNodes.append(node);        
    }
    hadUpdate = true;

    if(selectedNodes.size() == 1)
    {
        propertyWidgetManager->notifyNodeSelected(node);
    }
    else {
        propertyWidgetManager->notifyMultipleSelected();
    }
}

void SelectionManager::setSelected(VisualConnection *connection, bool clear)
{
    if(clear)
    {
        selectedNodes.clear();
        selectedConnections.clear();
    }
    if(!selectedConnections.contains(connection))
    {
        selectedConnections.append(connection);
    }
    hadUpdate = true;

    if(selectedNodes.size() == 0)
    {
        propertyWidgetManager->notifyNoneSelected();
    }
}
void SelectionManager::removeOne(VisualNodeBase* node)
{
    selectedNodes.removeOne(node);
    propertyWidgetManager->removeOne(node);
}
void SelectionManager::clearSelected()
{
    selectedNodes.clear();
    selectedConnections.clear();
    propertyWidgetManager->notifyNoneSelected();
}

bool SelectionManager::isUpdated()
{
    return hadUpdate;
}
void SelectionManager::clearUpdateFlag()
{
    hadUpdate = false;
}
