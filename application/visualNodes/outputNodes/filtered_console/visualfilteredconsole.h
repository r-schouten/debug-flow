#pragma once
#include <QJsonDocument>
#include<QJsonArray>

#include "visualnodebase.h"
#include "outputstyle.h"
#include "visualoutputnodebase.h"
#include "filteredconsole.h"
#include "globalconfig.h"
#include "filteredconsolepropertieswidget.h"

#include "serialization_handler.h"
#include "deserialization_handler.h"
class VisualFilteredConsole : public VisualOutputNodeBase, public OutputStyle
{
    Q_OBJECT
public:
    VisualFilteredConsole(FlowObjects *_flowObjects);
    VisualFilteredConsole(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    //calling an other constructor in C++ 11 compiles but doesn't work as expected, therefore a construct method
    void construct();
    virtual ~VisualFilteredConsole();

    void setWindowManager(WindowManager* _windowManager);
    void activate();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    VisualNodeBase *clone();

    QJsonObject* serialize(SerializationHandler &handler);

    //used by loadStore to check if node is this specific node type, its implemented in the class so its possible to make json files backward compatible when a className change
    static bool classNameEquals(QString name);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

private:
    FilteredConsole* node = nullptr;
    MdiWindow* window = nullptr;
};

