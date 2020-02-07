#pragma once

#include <QWidget>
#include <mdiwindow.cpp>
#include <QTimer>

#include "itemlist.h"
#include "visualnodeconfig.h"
#include "windowmanager.h"
#include "propertywidgetmanager.h"
#include "nodescene.h"
#include "ui_flow_widget.h"

#include "flowdata.h"
#include "loadstore.h"

#include "serialization_settings.h"
#include "deserialization_settings.h"
#include "serialization_error_log.h"
class FilteredConsole;
class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = nullptr);
    ~FlowWidget();

    void open(QJsonObject &jsonObject);
    QJsonObject *save();
private:
    Ui_flowWidget *m_ui = nullptr;

    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
    WindowManager* windowManager = nullptr;
    PropertyWidgetManager* propertyWidgetManager = nullptr;
    FlowData* flowData = nullptr;
    LoadStore* loadStore = nullptr;
public slots:
    void updateUI();

signals:

};

