#include "propertywidgetmanager.h"

PropertyWidgetManager::PropertyWidgetManager(QWidget* propertyWidget,QTabWidget* tabWidget)
    :propertyWidget(propertyWidget),tabWidget(tabWidget)
{
    widgetLayout = new QVBoxLayout;
    widgetLayout->setAlignment(Qt::AlignTop);

    propertyWidget->setLayout(widgetLayout);
    widgetLayout->setContentsMargins(0,0,0,0);

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

    tabWidget->setCurrentWidget(propertyWidget);

    widgetLayout->addWidget(node->loadPropertiesWidget(nullptr));
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
