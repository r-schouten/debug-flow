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

#include "serialization_handler.h"
#include "deserialization_handler.h"

#include "undoredomanager.h"

class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = nullptr);
    ~FlowWidget();

    void open(QJsonObject &jsonObject);
    QJsonObject *save();
    void undo();
    void redo();
private:
    Ui_flowWidget *flow_ui = nullptr;

    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
    WindowManager* windowManager = nullptr;
    PropertyWidgetManager* propertyWidgetManager = nullptr;
    FlowData* flowData = nullptr;
    LoadStore* loadStore = nullptr;
    UndoRedoManager* undoRedoManager = nullptr;
public slots:
    void updateUI();

signals:

};

