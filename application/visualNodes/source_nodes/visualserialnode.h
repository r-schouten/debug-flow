#pragma once

#include "serialnode.h"
#include "sourcestyle.h"
#include "visualnodebase.h"
#include "selectionmanager.h"
#include "visualsourcenodebase.h"

#include "combobox.h"

#include <QSerialPortInfo>
#include <QGraphicsProxyWidget>

class VisualSerialNode : public VisualSourceNodeBase
{
        Q_OBJECT
public:
    VisualSerialNode();
    VisualNodeBase *clone();

    ~VisualSerialNode();
    void activate();

public slots:
    void onComboBoxPopup(ComboBox *combobox);
    void onComboBoxChanged();
protected:
     SerialNode *node = nullptr;
    QGraphicsProxyWidget* proxyWidget = nullptr;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void loadSerialPorts();
    ComboBox* portComboBox = nullptr;
};

