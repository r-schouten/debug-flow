#pragma once
#include <QTreeWidgetItem>
#include "visualnodebase.h"

class MyTreeWidgetItem : public QTreeWidgetItem
{
public:
    MyTreeWidgetItem();
    ~MyTreeWidgetItem();
    void setNode(VisualNodeBase *node);
    VisualNodeBase* getNodeCopy();
private:
    VisualNodeBase* node = nullptr;
};

