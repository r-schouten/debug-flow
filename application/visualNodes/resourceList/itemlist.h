#pragma once
#include <QObject>
#include <QTreeWidget>
#include <QAbstractItemView>
#include <QStandardItemModel>

#include "flowobjects.h"
#include "mytreewidgetitem.h"

#include <visual_context_filter/visualcontextfilter.h>

#include "visualserialnode.h"
#include "nodescene.h"

#include "visualnodebase.h"

#include "visualfilteredconsole.h"
#include "visualserialnode.h"
#include "visualsimpleconsole.h"
#include "visualtestgeneratornode.h"
#include "visualtamplatenode.h"
class ItemList :public QObject
{
    Q_OBJECT
public:
    ItemList(QTreeWidget *resourceList, FlowObjects *_flowObjects, NodeScene *nodeScene);
    virtual ~ItemList();
private:
    QTreeWidget *resourceList = nullptr;
    FlowObjects *flowObjects = nullptr;
    DbgLogger* dbgLogger = nullptr;
    NodeScene* nodeScene = nullptr;
    QList<VisualNodeBase*> nodes;
    bool lastItemPressed = false;

    void generateList();

    template<typename T>
    void generateCategory(QList<VisualNodeBase *> &nodes, QString name, QString iconName);

public slots:
    void itemClicked(QTreeWidgetItem *item, int column);
};



