#include "scenecomponents.h"

void SceneComponents::setNodeScene(NodeScene *value)
{
    nodeScene = value;
}

SceneComponents::SceneComponents(QTreeWidget *resourceList,QTabWidget *tabWidget, QWidget *propertiesTab)
    :resourceList(resourceList),tabWidget(tabWidget),propertiesTab(propertiesTab)
{
    widgetNoneSelected = new PropertiesWidgetNoneSelected(propertiesTab);
    selectionManager = new SelectionManager(this);
}
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

SelectionManager *SceneComponents::getSelectionManager() const
{
    return selectionManager;
}

QTreeWidget *SceneComponents::getResourceList()
{
    return resourceList;
}
