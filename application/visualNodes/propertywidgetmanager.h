#pragma once
#include <QTabWidget>
#include <QScrollArea>
#include "visualnodebase.h"
#include "dbglogger.h"
#include "nodeinfoviewer.h"
class VisualNodeBase;
class NodeInfoViewer;
class PropertyWidgetManager
{
private:
    QScrollArea* propertyWidget = nullptr;
    QTabWidget* tabWidget = nullptr;
    VisualNodeBase* currentShownNode = nullptr;
    NodeInfoViewer* nodeViewer = nullptr;
    DbgLogger* dbgLogger = nullptr;
public:
    PropertyWidgetManager(QScrollArea *propertyWidget, QTabWidget *tabWidget, NodeInfoViewer* nodeViewer, DbgLogger* _dbgLogger);
    void notifyNodeSelected(VisualNodeBase* node);
    void notifyMultipleSelected();
    void notifyNoneSelected();

    void removeOne(VisualNodeBase *node);
};

