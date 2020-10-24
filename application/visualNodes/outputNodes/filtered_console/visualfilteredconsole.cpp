#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole(FlowObjects *_flowObjects)
    :VisualOutputNodeBase(_flowObjects)
{
    construct();
}

VisualFilteredConsole::VisualFilteredConsole(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualOutputNodeBase(_flowObjects, baseJson, handler)
{
    Q_UNUSED(derivedJson);
    construct();
    node->nodeSettings->deserialize(settingsJson, handler);
}

//calling an other constructor in C++ 11 compiles but doesn't work as expected, therefore a construct method
void VisualFilteredConsole::construct()
{
    name = "filtered console";
    shortDiscription = QString("this node provides a console with configurable filters for %1 context").arg(CONTEXT_STYLE_NAME);

    node = new FilteredConsole(flowObjects->getUpdateManager(),flowObjects->getHistoricalUpdateManager(), dbgLogger);
    connect(node->getNodeSettings(), SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));
    baseNode = node;
    if(node->amountOfInputs() > 0)
    {
        addInputConnector();
    }
    if(node->amountOfOutputs() > 0)
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
    }
    //node is already deleted with deleteMdiWindow(window);
    node = nullptr;
    baseNode = nullptr;

}

void VisualFilteredConsole::activate()
{
    window = windowManager->getMdiWindow(node);
}

PropertyWidgetBase *VisualFilteredConsole::loadPropertiesWidget(QWidget *parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new FilteredConsolePropertiesWidget(parent, dbgLogger, node->nodeSettings);
    }
    else {
        dbgLogger->warning(CLASSNAME,__FUNCTION__,"propertywidget already exist");
    }
    return propertyWidget;
}

void VisualFilteredConsole::releasePropertiesWidget()
{
    if(propertyWidget)
    {
        dbgLogger->debug(CLASSNAME,__FUNCTION__,"called");
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualFilteredConsole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

VisualNodeBase *VisualFilteredConsole::clone()
{
    return new VisualFilteredConsole(flowObjects);
}

QJsonObject *VisualFilteredConsole::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
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

