#include "visualconsistencychecker.h"


VisualConsistencyChecker::VisualConsistencyChecker(FlowObjects *_flowObjects)
    :VisualOutputNodeBase(_flowObjects)
{
    construct();
}

VisualConsistencyChecker::VisualConsistencyChecker(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
    :VisualOutputNodeBase(_flowObjects, baseJson, handler)
{
     Q_UNUSED(derivedJson)
     construct();
     settings->deserialize(settingsJson, handler);
}

VisualConsistencyChecker::~VisualConsistencyChecker()
{
    if(window)
    {
        windowManager->deleteMdiWindow(window);
    }
    //node is already deleted with deleteMdiWindow(window);
    node = nullptr;
    baseNode = nullptr;
}

void VisualConsistencyChecker::construct()
{
    node = new ConsistencyCheckerNode(flowObjects->getUpdateManager(),dbgLogger, flowObjects->getHistoricalUpdateManager());
    baseNode = node;

    settings = node->getNodeSettings();

    connect(settings, SIGNAL(saveAbleChangeOccured()),flowObjects->getUndoRedoManager(),SLOT(notifySettingsChanged()));

    name = "consistency checker";
    shortDiscription = "a node to check whether there are errors in the system";
    if(node->amountOfInputs() > 0)
    {
        addInputConnector();
    }
    if(node->amountOfOutputs() > 0)
    {
        addOutputConnector();
    }
    height = 50;
}

//create a new instance of such node, this function is used to make a new node from the resourceList.
VisualNodeBase *VisualConsistencyChecker::clone()
{
    return new VisualConsistencyChecker(flowObjects);
}

//the resource list makes node instances just for the paint function.
//in such case the activate function is not called and memory or performance wasting things should not be activated
void VisualConsistencyChecker::activate()
{
    activated = true;
    window = windowManager->getMdiWindow(node);
}

void VisualConsistencyChecker::setWindowManager(WindowManager *_windowManager)
{
    if(_windowManager == nullptr)
    {
        qFatal("[fatal][VisualFiteredConsole] windowManager == nullptr");
    }
    windowManager = _windowManager;
}

//serialize every variable which need to be saved, and which is owned by this (derived) node
//JSON_NODE_TYPE is deserialized by the loadstore class.
QJsonObject *VisualConsistencyChecker::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_NODE_TYPE, CLASSNAME);

    return jsonObject;
}
//deserialization handler not added yet because there are no variables to deserialize

//used by loadstore to deserialize nodes
bool VisualConsistencyChecker::classNameEquals(QString name)
{
    if(name.compare(staticMetaObject.className(),Qt::CaseInsensitive) == 0)
    {
        return true;
    }
    return false;
}

PropertyWidgetBase *VisualConsistencyChecker::loadPropertiesWidget(QWidget *parent)
{
    if(propertyWidget == nullptr)
    {
        propertyWidget = new ConsistencyCheckerPropertiesWidget(parent, dbgLogger, settings);
    }
    else {
        dbgLogger->warning(CLASSNAME,__FUNCTION__,"propertywidget already exist");
    }
    return propertyWidget;
}

void VisualConsistencyChecker::releasePropertiesWidget()
{
    if(propertyWidget != nullptr)
    {
        delete propertyWidget;
        propertyWidget = nullptr;
    }
}

void VisualConsistencyChecker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setRenderHints(QPainter::TextAntialiasing, true);

    paintBase(painter,this,"consistency checker");
    drawConnectors(painter, this);


    painter->setPen(textPen);
    painter->setFont(textFont);

}

void VisualConsistencyChecker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    VisualOutputNodeBase::mousePressEvent(event);
}




