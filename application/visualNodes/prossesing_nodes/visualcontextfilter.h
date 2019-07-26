#pragma once
#include "visualnodebase.h"
#include "contextfilternode.h"
#include "processingstyle.h"
#include "contextfilter.h"

class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter();
    ~VisualContextFilter();
protected:
    ContextFilterNode* node = nullptr;
    void activate();
    VisualNodeBase *clone();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ContextFilter* contextFilter = nullptr;
};

