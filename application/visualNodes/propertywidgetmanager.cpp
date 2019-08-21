#include "propertywidgetmanager.h"

PropertyWidgetManager::PropertyWidgetManager(QWidget* propertyWidget,QTabWidget* tabWidget)
    :propertyWidget(propertyWidget),tabWidget(tabWidget)
{

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
    qDebug("[debug][propertyWidgetManager] open properties");

    currentShownNode = node;

    tabWidget->setCurrentWidget(propertyWidget);

    node->loadPropertiesWidget(propertyWidget);
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
