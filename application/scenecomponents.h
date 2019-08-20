//this class carries important compontents for the scene, a instance is passed to all nodes
#pragma once
#include <QTreeWidget>
#include <propertieswidgetnoneselected.h>

class NodeScene;
class SceneComponents
{
private:
    QTreeWidget *resourceList = nullptr;
    NodeScene *nodeScene = nullptr;
    QTabWidget *tabWidget = nullptr;
    QWidget *propertiesTab = nullptr;
    PropertiesWidgetNoneSelected *widgetNoneSelected = nullptr;
public:
    SceneComponents(QTreeWidget *resourceList,NodeScene *nodeScene, QTabWidget *tabWidget, QWidget *propertiesTab)
        :resourceList(resourceList), nodeScene(nodeScene),tabWidget(tabWidget),propertiesTab(propertiesTab)
    {
        widgetNoneSelected = new PropertiesWidgetNoneSelected(propertiesTab);
    }

    QTreeWidget *getResourceList();
    NodeScene *getNodeScene();
    QTabWidget *getTabWidget() const;
    QWidget *getPropertiesTab() const;
    PropertiesWidgetNoneSelected *getWidgetNoneSelected() const;
};

