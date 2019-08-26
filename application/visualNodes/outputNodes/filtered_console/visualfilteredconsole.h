#pragma once
#include "visualnodebase.h"
#include "outputstyle.h"
#include "visualoutputnodebase.h"
#include "filteredconsole.h"
#include "globalconfig.h"
#include "filteredconsolepropertieswidget.h"

class VisualFilteredConsole : public VisualOutputNodeBase, public OutputStyle
{
    Q_OBJECT
public:
    VisualFilteredConsole();
    void setWindowManager(WindowManager* _windowManager);
    void activate();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();
    ~VisualFilteredConsole();
protected:
    QWidget *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

private:
    FilteredConsole* node = nullptr;
    MdiWindow* window = nullptr;
};

