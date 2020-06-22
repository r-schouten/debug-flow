#include "propertywidgetmanager.h"


PropertyWidgetManager::PropertyWidgetManager(QScrollArea* propertyWidget, QTabWidget* tabWidget, DbgLogger *_dbgLogger)
    :propertyWidget(propertyWidget),tabWidget(tabWidget),dbgLogger(_dbgLogger)
{

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    propertyWidget->setSizePolicy(sizePolicy);
}

void PropertyWidgetManager::notifyNodeSelected(VisualNodeBase *node)
{
    if(currentShownNode != nullptr)
    {
        if(node != currentShownNode)
        {
            currentShownNode->releasePropertiesWidget();
            currentShownNode = nullptr;
        }
    }

    currentShownNode = node;

    QWidget * nodePropertiesWidget = node->loadPropertiesWidget(nullptr);
    if(nodePropertiesWidget == nullptr)
    {
        dbgLogger->error("PropertyWidgetManager",__FUNCTION__, "returned NULL");
        return;
    }
    propertyWidget->setWidget(nodePropertiesWidget);
}

void PropertyWidgetManager::notifyMultipleSelected()
{
    if(currentShownNode != nullptr)
    {
        currentShownNode->releasePropertiesWidget();
        currentShownNode = nullptr;
    }
}

void PropertyWidgetManager::notifyNoneSelected()
{
    if(currentShownNode != nullptr)
    {
        currentShownNode->releasePropertiesWidget();
        currentShownNode = nullptr;
    }
}
void PropertyWidgetManager::removeOne(VisualNodeBase* node)
{
    if(node == currentShownNode)
    {
        currentShownNode = nullptr;
    }
}
