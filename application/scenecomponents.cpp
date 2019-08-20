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

PropertiesWidgetNoneSelected *SceneComponents::getWidgetNoneSelected() const
{
    return widgetNoneSelected;
}

QTreeWidget *SceneComponents::getResourceList()
{
    return resourceList;
}
