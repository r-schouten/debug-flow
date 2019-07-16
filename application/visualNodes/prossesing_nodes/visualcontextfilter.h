#pragma once
#include "visualnodebase.h"
#include "contextfilter.h"

class VisualContextFilter : public VisualNodeBase
{
public:
    VisualContextFilter();
protected:
    ContextFilter* node = nullptr;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

