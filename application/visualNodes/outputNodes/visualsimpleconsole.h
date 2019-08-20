#pragma once
#include "visualnodebase.h"
#include "outputstyle.h"
#include "visualoutputnodebase.h"
#include "simpleconsole.h"

class VisualSimpleConsole : public VisualOutputNodeBase, public OutputStyle
{
public:
    VisualSimpleConsole(SceneComponents *sceneComponents);
    ~VisualSimpleConsole();
    void setWindowManager(WindowManager* _windowManager);
    void activate();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();
private:
    SimpleConsole* node = nullptr;
    MdiWindow* window = nullptr;
};
