#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <mdiwindow.cpp>
#include <QMenuBar>

#include "propertywidgetmanager.h"
#include "nodescene.h"
#include "ui_mainwindow.h"
#include "itemlist.h"
#include "visualnodeconfig.h"
#include "windowmanager.h"


QT_BEGIN_NAMESPACE
class QMenuBar;
class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class FilteredConsole;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateUI();
private slots:
    void newFlow();
    void openFlow();
    void saveFlow();
    void closeFlow();
    void pauseFlow();
    void resumeFlow();
    void clearFlow();
private:
    Ui::MainWindow *m_ui = nullptr;
    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
    WindowManager* windowManager = nullptr;
    PropertyWidgetManager* propertyWidgetManager = nullptr;

    QMenu *windowMenu = nullptr;
    QAction *newAction = nullptr;
    QAction *openAction = nullptr;
    QAction *saveAction = nullptr;
    QAction *pauseAction = nullptr;
    QAction *resetAction = nullptr;
    QAction *resumeAction = nullptr;
    void createToolbar();



};
