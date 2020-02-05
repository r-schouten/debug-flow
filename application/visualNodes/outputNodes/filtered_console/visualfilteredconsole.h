#pragma once
#include <QJsonDocument>
#include<QJsonArray>

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
    ~VisualFilteredConsole();

    void setWindowManager(WindowManager* _windowManager);
    void activate();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();

    QJsonObject* serialize();
    void deserialize(QJsonObject* jsonObject);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

private:
    FilteredConsole* node = nullptr;
    MdiWindow* window = nullptr;
};

