#pragma once
#include <QSerialPortInfo>
#include <QGraphicsProxyWidget>

#include <QJsonObject>

#include "serialnode.h"
#include "sourcestyle.h"
#include "visualnodebase.h"
#include "selectionmanager.h"
#include "visualsourcenodebase.h"
#include "serialnodepropertieswidget.h"

#include "combobox.h"

class VisualSerialNode : public VisualSourceNodeBase
{
    Q_OBJECT
public:
    VisualSerialNode(FlowObjects *_flowObjects);
    VisualSerialNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    VisualNodeBase *clone();

    virtual ~VisualSerialNode();
    void activate();

    void openPort();

    QJsonObject* serialize(SerializationHandler &handler);
    //used by loadStore to check if node is this specific node type, its implemented in the class so its possible to make json files backward compatible when a className change
    static bool classNameEquals(QString name);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool activated = false;
    SerialNode *node = nullptr;
    SerialSettings* serialSettings = nullptr;
private:
    void construct();
};

