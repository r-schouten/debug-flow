#include "propertywidgetmanager.h"


PropertyWidgetManager::PropertyWidgetManager(QScrollArea *propertyWidget, QTabWidget *tabWidget, NodeInfoViewer *nodeViewer, DbgLogger *_dbgLogger)
    :propertyWidget(propertyWidget),tabWidget(tabWidget),nodeViewer(nodeViewer),dbgLogger(_dbgLogger)
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

    nodeViewer->nodeSelected(node);
}

void PropertyWidgetManager::notifyMultipleSelected()
{
    if(currentShownNode != nullptr)
    {
        currentShownNode->releasePropertiesWidget();
        currentShownNode = nullptr;
    }

    nodeViewer->nodeDeselected();
}

void PropertyWidgetManager::notifyNoneSelected()
{
    if(currentShownNode != nullptr)
    {
        currentShownNode->releasePropertiesWidget();
        currentShownNode = nullptr;
    }
    nodeViewer->nodeDeselected();
}
void PropertyWidgetManager::removeOne(VisualNodeBase* node)
{
    if(node == currentShownNode)
    {
        nodeViewer->nodeDeselected();
        currentShownNode = nullptr;
    }
}
