#pragma once
#include <QTabWidget>
#include <QVBoxLayout>
#include "visualnodebase.h"

class VisualNodeBase;
class PropertyWidgetManager
{
private:
    QWidget* propertyWidget = nullptr;
    QTabWidget* tabWidget = nullptr;
    VisualNodeBase* currentShownNode = nullptr;

    QVBoxLayout *widgetLayout = nullptr;
public:
    PropertyWidgetManager(QWidget *propertyWidget, QTabWidget *tabWidget);
    void notifyNodeSelected(VisualNodeBase* node);
    void notifyMultipleSelected();
    void notifyNoneSelected();

    void removeOne(VisualNodeBase *node);
};

