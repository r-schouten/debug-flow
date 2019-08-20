#pragma once
#include "visualnodebase.h"
#include "outputstyle.h"
#include "visualoutputnodebase.h"
#include "filteredconsole.h"
#include "globalconfig.h"

class VisualFilteredConsole : public VisualOutputNodeBase, public OutputStyle
{
    Q_OBJECT
public:
    VisualFilteredConsole(SceneComponents *sceneComponents);
    void setWindowManager(WindowManager* _windowManager);
    void activate();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();
    ~VisualFilteredConsole();
private:
    FilteredConsole* node = nullptr;
    MdiWindow* window = nullptr;
};

