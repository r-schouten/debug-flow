#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole()
{

    name = "filtered console";
    shortDiscription = QString("this node provides a console with configurable filters for %1 context").arg(CONTEXT_STYLE_NAME);
};

void VisualFilteredConsole::setWindowManager(WindowManager *_windowManager)
{
    qDebug("[debug][VisualFiteredConsole] setWindowManager");
    if(_windowManager == nullptr)
    {
        qFatal("[fatal][VisualFiteredConsole] windowManager == nullptr");
    }
    windowManager = _windowManager;

    node = new FilteredConsole();
    baseNode = node;
    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
}

VisualFilteredConsole::~VisualFilteredConsole()
{
    if(window)
    {
        windowManager->deleteMdiWindow(window);
        baseNode = nullptr;
    }
}

void VisualFilteredConsole::activate()
{
    window = windowManager->getMdiWindow(node);
}

PropertyWidgetBase *VisualFilteredConsole::loadPropertiesWidget(QWidget *parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new FilteredConsolePropertiesWidget(parent,node->nodeSettings);
    }
    else {
        qDebug("[warn][VisualFilteredConsole::loadPropertiesWidget] propertywidget already exist");
    }
    return propertyWidget;
}

void VisualFilteredConsole::releasePropertiesWidget()
{
    if(propertyWidget)
    {
        qDebug("[debug][VisualFilteredConsole::releasePropertiesWidget]");
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualFilteredConsole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

VisualNodeBase *VisualFilteredConsole::clone()
{
    return new VisualFilteredConsole();
}

QJsonObject *VisualFilteredConsole::serialize()
{
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert("type",metaObject()->className());

    return jsonObject;
}
void VisualFilteredConsole::deserialize(QJsonObject *jsonObject)
{

}
