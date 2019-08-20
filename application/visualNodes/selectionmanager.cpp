#include "selectionmanager.h"

SelectionManager::SelectionManager(SceneComponents* sceneComponents)
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
}
void SelectionManager::clearSelected()
{
    selectedNodes.clear();
    selectedConnections.clear();
}

bool SelectionManager::isUpdated()
{
    return hadUpdate;
}
void SelectionManager::clearUpdateFlag()
{
    hadUpdate = false;
}
