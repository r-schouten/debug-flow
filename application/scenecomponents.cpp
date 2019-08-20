#include "scenecomponents.h"

NodeScene *SceneComponents::getNodeScene()
{
    return nodeScene;
}

QTabWidget *SceneComponents::getTabWidget() const
{
    return tabWidget;
}

QWidget *SceneComponents::getPropertiesTab() const
{
    return propertiesTab;
}

QTreeWidget *SceneComponents::getResourceList()
{
    return resourceList;
}
