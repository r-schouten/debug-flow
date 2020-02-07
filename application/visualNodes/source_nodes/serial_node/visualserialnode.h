#pragma once
#include <QSerialPortInfo>
#include <QGraphicsProxyWidget>

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
    VisualSerialNode();
    VisualNodeBase *clone();

    ~VisualSerialNode();
    void activate();

    void openPort();

    QJsonObject* serialize(SerializationHandler &handler);
protected:
    PropertyWidgetBase *loadPropertiesWidget(QWidget *parent);
    void releasePropertiesWidget();

    SerialNode *node = nullptr;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool activated = false;

};

