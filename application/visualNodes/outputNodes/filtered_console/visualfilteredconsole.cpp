#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole()
{
    construct();
}

VisualFilteredConsole::VisualFilteredConsole(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualOutputNodeBase(baseJson, handler)
{
    construct();
    node->nodeSettings->deserialize(settingsJson, handler);
}

//calling an other constructor in C++ 11 compiles but doesn't work as expected, therefore a construct method
void VisualFilteredConsole::construct()
{
    name = "filtered console";
    shortDiscription = QString("this node provides a console with configurable filters for %1 context").arg(CONTEXT_STYLE_NAME);

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
void VisualFilteredConsole::setWindowManager(WindowManager *_windowManager)
{
    if(_windowManager == nullptr)
    {
        qFatal("[fatal][VisualFiteredConsole] windowManager == nullptr");
    }
    windowManager = _windowManager;
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

QJsonObject *VisualFilteredConsole::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_NODE_TYPE, CLASSNAME);

    return jsonObject;
}

bool VisualFilteredConsole::classNameEquals(QString name)
{
    if(name.compare(staticMetaObject.className(),Qt::CaseInsensitive) == 0)
    {
        return true;
    }
    return false;
}

