#pragma once

#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

#include "propertywidgetbase.h"
#include "consistencycheckersettings.h"

class ConsistencyCheckerPropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    ConsistencyCheckerPropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, ConsistencyCheckerSettings *settings);
    virtual ~ConsistencyCheckerPropertiesWidget();

private slots:
    void showAllChanged(int);
    void historicalUpdateClicked(bool);
private:
    ConsistencyCheckerSettings* settings = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    QWidget *formContainter = nullptr;
    QFormLayout *formLayout = nullptr;

    QWidget *container = nullptr;
    QVBoxLayout *containerLayout = nullptr;

    QCheckBox* showAll = nullptr;
    QPushButton* historicalUpdateButton = nullptr;

};


