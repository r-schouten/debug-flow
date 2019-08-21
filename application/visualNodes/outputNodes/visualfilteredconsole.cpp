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

QWidget *VisualFilteredConsole::loadPropertiesWidget(QWidget *parent)
{

}

void VisualFilteredConsole::releasePropertiesWidget()
{

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
