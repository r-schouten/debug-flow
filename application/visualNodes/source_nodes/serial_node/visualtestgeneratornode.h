#pragma once

#include <QJsonObject>

#include "sourcestyle.h"
#include "selectionmanager.h"
#include "visualsourcenodebase.h"
#include "testgeneratornode.h"
#include "testgeneratorpropertieswidget.h"

class VisualTestGeneratorNode : public VisualSourceNodeBase
{
    Q_OBJECT
public:
    VisualTestGeneratorNode(FlowObjects *_flowObjects);
    VisualTestGeneratorNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    VisualNodeBase *clone();

    virtual ~VisualTestGeneratorNode();
    void activate();

    QJsonObject *serialize(SerializationHandler &handler);

    //used by loadStore to check if node is this specific node type, its implemented in the class so its possible to make json files backward compatible when a className change
    static bool classNameEquals(QString name);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);


    bool activated = false;
    TestGeneratorNode *node = nullptr;
    NodeSettingsBase* settings = nullptr;
private:
    void construct();

};

