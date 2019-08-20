//this class carries important compontents for the scene, a instance is passed to all nodes
#pragma once
#include <QTreeWidget>

class NodeScene;
class SceneComponents
{
private:
    QTreeWidget *resourceList = nullptr;
    NodeScene *nodeScene = nullptr;
    QTabWidget *tabWidget = nullptr;
    QWidget *propertiesTab = nullptr;
public:
    SceneComponents(QTreeWidget *resourceList,NodeScene *nodeScene, QTabWidget *tabWidget, QWidget *propertiesTab)
        :resourceList(resourceList), nodeScene(nodeScene),tabWidget(tabWidget),propertiesTab(propertiesTab){}

    QTreeWidget *getResourceList();
    NodeScene *getNodeScene();
    QTabWidget *getTabWidget() const;
    QWidget *getPropertiesTab() const;
};

