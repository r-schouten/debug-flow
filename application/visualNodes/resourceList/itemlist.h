#pragma once
#include <QObject>
#include <QTreeWidget>
#include <QAbstractItemView>
#include <QStandardItemModel>

#include "mytreewidgetitem.h"

#include "visualcontextfilter.h"
#include "visualserialnode.h"
#include "nodescene.h"

#include "visualnodebase.h"
class ItemList :public QObject
{
    Q_OBJECT
private:
    QTreeWidget *resourceList = nullptr;
    NodeScene* nodeScene = nullptr;
    QList<VisualNodeBase*> nodes;
    bool lastItemPressed = false;
    void generateList();

    template<typename T>
    void generateCategory(QList<VisualNodeBase *> &nodes, QString name, QString iconName);
public:
    ItemList(QTreeWidget* resourceList, NodeScene* nodeScene);
public slots:
    void itemClicked(QTreeWidgetItem *item, int column);
    void itemPressed(QTreeWidgetItem *item, int column);
};



