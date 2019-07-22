#pragma once
#include "visualnodebase.h"
#include "outputstyle.h"

#include "filteredconsole.h"

class VisualFilteredConsole : public VisualNodeBase, public OutputStyle
{
    Q_OBJECT
public:
    VisualFilteredConsole();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();
    ~VisualFilteredConsole();

private:
    FilteredConsole* node = nullptr;
};

