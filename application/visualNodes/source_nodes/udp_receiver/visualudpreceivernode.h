#pragma once

#include <QJsonObject>
#include "selectionmanager.h"
#include "udpreceiver.h"
#include "udpreceiversettings.h"
#include "udpreceivernodepropertieswidget.h"

#include "visualsourcenodebase.h"

class VisualUdpReceiverNode : public VisualSourceNodeBase
{
    Q_OBJECT
public:
    VisualUdpReceiverNode(FlowObjects *_flowObjects);
    VisualUdpReceiverNode(FlowObjects *_flowObjects, QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
    VisualNodeBase *clone();

    virtual ~VisualUdpReceiverNode();
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
    UdpReceiver *node = nullptr;
    UdpReceiverSettings* settings = nullptr;

private:
    void construct();
};

