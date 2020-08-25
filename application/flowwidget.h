#pragma once

#include <QWidget>
#include <QTimer>

#include "mdiwindow.cpp"
#include "filesystem.h"
#include "dbglogger.h"
#include "itemlist.h"
#include "visualnodeconfig.h"
#include "windowmanager.h"
#include "propertywidgetmanager.h"
#include "nodescene.h"
#include "updatemanager.h"
#include "ui_flow_widget.h"

#include "loadstore.h"

#include "serialization_handler.h"
#include "deserialization_handler.h"

#include "undoredomanager.h"
#include "historicalupdatemanager.h"
#include "flowobjects.h"

class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = nullptr, FileSystem* _fileSystem = nullptr);
    virtual ~FlowWidget();

    void open(QJsonObject &jsonObject);
    bool save(bool saveAs);

    void undo();
    void redo();
    bool getchangesSaved();
    QString getFileName();
private:
    Ui_flowWidget *flow_ui = nullptr;

    DbgLogger *dbgLogger = nullptr;
    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
    WindowManager* windowManager = nullptr;
    PropertyWidgetManager* propertyWidgetManager = nullptr;
    LoadStore* loadStore = nullptr;
    FileSystem* fileSystem = nullptr;
    UndoRedoManager* undoRedoManager = nullptr;
    FlowObjects* flowObjects = nullptr;
    SelectionManager* selectionManager = nullptr;
    HistoricalUpdateManager* historicalUpdateManager = nullptr;
    UpdateManager* updateManager = nullptr;
    bool changesSaved = false;
public slots:
    void updateUI();

    void anythingChanged();
signals:
    void setTabName(QWidget* tabe, QString tabName);
};

