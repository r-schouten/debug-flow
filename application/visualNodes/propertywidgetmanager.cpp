#include "propertywidgetmanager.h"


PropertyWidgetManager::PropertyWidgetManager(QScrollArea* propertyWidget,QTabWidget* tabWidget)
    :propertyWidget(propertyWidget),tabWidget(tabWidget)
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

    qDebug("[debug][propertyWidgetManager] open properties");

    currentShownNode = node;

    //tabWidget->setCurrentWidget(propertyWidget);
    QWidget * nodePropertiesWidget = node->loadPropertiesWidget(nullptr);
    if(nodePropertiesWidget == nullptr)
    {
        qDebug("[error][propertyWidgetManager] node->loadPropertiesWidget() returned NULL");
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
