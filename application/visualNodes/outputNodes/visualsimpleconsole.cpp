#include "visualsimpleconsole.h"

VisualSimpleConsole::VisualSimpleConsole(FlowObjects *_flowObjects)
    :VisualOutputNodeBase(_flowObjects)
{
    name = "simple console";
    shortDiscription = "this node provides a simple console";
}

VisualSimpleConsole::~VisualSimpleConsole()
{
    if(window)
    {
        windowManager->deleteMdiWindow(window);
    }
    //node is already deleted  with windowManager->deleteMdiWindow(window);
    node = nullptr;
    baseNode = nullptr;
}


void VisualSimpleConsole::activate()
{
    window = windowManager->getMdiWindow(node);
}

PropertyWidgetBase *VisualSimpleConsole::loadPropertiesWidget(QWidget* parent)
{
    Q_UNUSED(parent);
    return nullptr;
}

void VisualSimpleConsole::releasePropertiesWidget()
{

}

void VisualSimpleConsole::setWindowManager(WindowManager *_windowManager)
{
    qDebug("[debug][SimpleConsole] setWindowManager");
    if(_windowManager == nullptr)
    {
        qFatal("[fatal][SimpleConsole] windowManager == nullptr");
    }
    windowManager = _windowManager;

    node = new SimpleConsole(flowObjects->getUpdateManager(),dbgLogger);
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

void VisualSimpleConsole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

VisualNodeBase *VisualSimpleConsole::clone()
{
    return new VisualSimpleConsole(flowObjects);
}

QJsonObject *VisualSimpleConsole::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    return nullptr;
}


