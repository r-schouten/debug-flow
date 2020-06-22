#pragma once
#include <QFormLayout>
#include <QWidget>

#include "nodesettingsbase.h"

class PropertyWidgetBase : public QWidget
{
    Q_OBJECT
private:
    NodeSettingsBase* settings;
protected:
    DbgLogger* dbgLogger = nullptr;
public:
    explicit PropertyWidgetBase(QWidget *parent, DbgLogger* dbgLogger);
    virtual ~PropertyWidgetBase();
};

