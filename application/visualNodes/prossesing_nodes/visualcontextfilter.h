#pragma once
#include "visualnodebase.h"
#include "contextfilter.h"
#include "processingstyle.h"
class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter();
    ~VisualContextFilter();
protected:
    ContextFilter* node = nullptr;
    void activate();
    NodeBase *getNode();
    VisualNodeBase *clone();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

