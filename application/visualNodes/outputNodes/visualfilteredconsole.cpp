#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole()
{

    name = "filtered console";
    shortDiscription = "this node provides a console with configurable filters for debug flow style context";
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

void VisualFilteredConsole::activate()
{
    window = windowManager->getMdiWindow(node);
}

VisualFilteredConsole::~VisualFilteredConsole()
{
    if(window)
    {
        windowManager->deleteMdiWindow(window);
        baseNode = nullptr;
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
