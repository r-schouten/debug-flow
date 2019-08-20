//this class carries important compontents for the scene, a instance is passed to all nodes and connections
#pragma once
#include <QTreeWidget>
#include "propertieswidgetnoneselected.h"
#include "selectionmanager.h"

class NodeScene;
class SelectionManager;
class SceneComponents
{
private:
    QTreeWidget *resourceList = nullptr;
    NodeScene *nodeScene = nullptr;
    QTabWidget *tabWidget = nullptr;
    QWidget *propertiesTab = nullptr;
    PropertiesWidgetNoneSelected *widgetNoneSelected = nullptr;
    SelectionManager* selectionManager = nullptr;
public:
    SceneComponents(QTreeWidget *resourceList, QTabWidget *tabWidget, QWidget *propertiesTab);

    QTreeWidget *getResourceList();
    NodeScene *getNodeScene();
    QTabWidget *getTabWidget() const;
    QWidget *getPropertiesTab() const;
    PropertiesWidgetNoneSelected *getWidgetNoneSelected() const;
    SelectionManager *getSelectionManager() const;
    void setNodeScene(NodeScene *value);
};

