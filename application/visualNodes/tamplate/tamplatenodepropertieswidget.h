#pragma once

#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

#include "propertywidgetbase.h"
#include "tamplatenodesettings.h"

class TamplateNodePropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    TamplateNodePropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, TamplateNodeSettings *settings);
    virtual ~TamplateNodePropertiesWidget();

private slots:

    void startStopClicked();
private:
    TamplateNodeSettings* settings = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    QWidget *formContainter = nullptr;
    QFormLayout *formLayout = nullptr;

    QWidget *container = nullptr;
    QVBoxLayout *containerLayout = nullptr;


    QPushButton* startStop = nullptr;


};


