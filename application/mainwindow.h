#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <mdiwindow.cpp>

#include "nodescene.h"
#include "ui_mainwindow.h"


#include "itemlist.h"
#include "visualnodeconfig.h"

#include "windowmanager.h"
QT_BEGIN_NAMESPACE

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


private:
    Ui::MainWindow *m_ui = nullptr;
    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
    WindowManager* windowManager = nullptr;
};
