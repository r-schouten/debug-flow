#pragma once
#include <QTabWidget>
#include <QScrollArea>
#include "visualnodebase.h"
#include "dbglogger.h"

class VisualNodeBase;
class PropertyWidgetManager
{
private:
    QScrollArea* propertyWidget = nullptr;
    QTabWidget* tabWidget = nullptr;
    VisualNodeBase* currentShownNode = nullptr;
    DbgLogger* dbgLogger = nullptr;
public:
    PropertyWidgetManager(QScrollArea *propertyWidget, QTabWidget *tabWidget, DbgLogger* _dbgLogger);
    void notifyNodeSelected(VisualNodeBase* node);
    void notifyMultipleSelected();
    void notifyNoneSelected();

    void removeOne(VisualNodeBase *node);
};

