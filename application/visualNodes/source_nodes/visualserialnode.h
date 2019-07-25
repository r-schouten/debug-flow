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

    void openPort();
public slots:
    void onComboBoxChanged();
    void loadSerialPorts();

    void handleSerialPortError(QSerialPort::SerialPortError);
    void onBaudRateChanged();
protected:
     SerialNode *node = nullptr;
    QGraphicsProxyWidget* proxyWidget = nullptr;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ComboBox* portComboBox = nullptr;
    bool activated = false;
    bool lockCombobox = false;

    QGraphicsProxyWidget* baudRateProxyWidget = nullptr;
    QComboBox* baudRateCombobox = nullptr;
    const int defaultBaudRate = 9600;
};

