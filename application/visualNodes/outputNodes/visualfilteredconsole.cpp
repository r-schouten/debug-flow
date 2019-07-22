#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole()
{

    name = "filtered console";
}

void VisualFilteredConsole::setWindowManager(WindowManager *_windowManager)
{
    qDebug("[debug][VisualFiteredConsole] setWindowManager");
    if(_windowManager == nullptr)
    {
        qFatal("[fatal][VisualFiteredConsole] windowManager == nullptr");
    }
    windowManager = _windowManager;

    node = new FilteredConsole();

    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
}

void VisualFilteredConsole::activate()
{
    window = windowManager->getMdiWindow(node);
}

NodeBase *VisualFilteredConsole::getNode()
{
    return node;
}

VisualFilteredConsole::~VisualFilteredConsole()
{
    if(window)
    {
        windowManager->deleteMdiWindow(window);
    }
}
void VisualFilteredConsole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintBase(painter,this,name);
    drawConnectors(painter,this);
}

VisualNodeBase *VisualFilteredConsole::clone()
{
    return new VisualFilteredConsole;
}
