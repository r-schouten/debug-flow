#pragma once

#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

#include "propertywidgetbase.h"
#include "udpreceiversettings.h"


class UdpReceiverNodePropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    UdpReceiverNodePropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, UdpReceiverSettings *settings);
    virtual ~UdpReceiverNodePropertiesWidget();

private slots:

    void startStopClicked();
private:
    UdpReceiverSettings* settings = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    QWidget *formContainter = nullptr;
    QFormLayout *formLayout = nullptr;

    QWidget *container = nullptr;
    QVBoxLayout *containerLayout = nullptr;



    QPushButton* startStop = nullptr;

};

