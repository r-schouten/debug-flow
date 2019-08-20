#pragma once
#include "visualnodebase.h"
#include "contextfilternode.h"
#include "processingstyle.h"
#include "contextfilter.h"
#include "globalconfig.h"
class VisualContextFilter : public VisualNodeBase, public ProcessingStyle
{
    Q_OBJECT
public:
    VisualContextFilter(SceneComponents *sceneComponents);
    ~VisualContextFilter();
protected:
    ContextFilterNode* node = nullptr;
    void activate();
    VisualNodeBase *clone();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ContextFilter* contextFilter = nullptr;
};

