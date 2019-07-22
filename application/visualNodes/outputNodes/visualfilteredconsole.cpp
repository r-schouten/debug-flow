#include "visualfilteredconsole.h"

VisualFilteredConsole::VisualFilteredConsole()
{
    node = new FilteredConsole();
    name = "filtered console";
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
    if(node)
    {
        delete node;
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
