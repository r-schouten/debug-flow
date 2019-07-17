#pragma once
#include "visualnodebase.h"
#include "contextfilter.h"
#include "processingstyle.h"
class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter();
protected:
    ContextFilter* node = nullptr;
    VisualNodeBase *clone();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

