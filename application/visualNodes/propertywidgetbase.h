#pragma once
#include <QFormLayout>
#include <QWidget>

#include "nodesettingsbase.h"

class PropertyWidgetBase : public QWidget
{
    Q_OBJECT
private:
    NodeSettingsBase* settings;
public:
    explicit PropertyWidgetBase(QWidget *parent);
    virtual ~PropertyWidgetBase();
};

