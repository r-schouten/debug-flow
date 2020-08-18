#pragma once

#include <QJsonObject>
#include "selectionmanager.h"
#include "consistencycheckernode.h"
#include "consistencycheckerpropertieswidget.h"
#include "consistencycheckersettings.h"


#include "outputstyle.h"
#include "visualoutputnodebase.h"

class VisualConsistencyChecker : public VisualOutputNodeBase, public OutputStyle
{
    Q_OBJECT
public:
    VisualConsistencyChecker(FlowObjects *_flowObjects);
    VisualConsistencyChecker(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    VisualNodeBase *clone();

    virtual ~VisualConsistencyChecker();
    void activate();
    void setWindowManager(WindowManager *_windowManager);

    QJsonObject *serialize(SerializationHandler &handler);

    //used by loadStore to check if node is this specific node type, its implemented in the class so its possible to make json files backward compatible when a className change
    static bool classNameEquals(QString name);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


    bool activated = false;
    ConsistencyCheckerNode *node = nullptr;
    ConsistencyCheckerSettings* settings = nullptr;

private:
    void construct();
    MdiWindow* window = nullptr;
};

