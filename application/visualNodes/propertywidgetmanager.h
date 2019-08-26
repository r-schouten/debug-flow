#pragma once
#include <QTabWidget>
#include <QVBoxLayout>
#include "visualnodebase.h"
#include <QScrollArea>

class VisualNodeBase;
class PropertyWidgetManager
{
private:
    QScrollArea* propertyWidget = nullptr;
    QTabWidget* tabWidget = nullptr;
    VisualNodeBase* currentShownNode = nullptr;

public:
    PropertyWidgetManager(QScrollArea *propertyWidget, QTabWidget *tabWidget);
    void notifyNodeSelected(VisualNodeBase* node);
    void notifyMultipleSelected();
    void notifyNoneSelected();

    void removeOne(VisualNodeBase *node);
};

