#pragma once

#include <iostream>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsView>
#include <mdiwindow.cpp>

#include "nodescene.h"
#include "visualserialnode.h"
#include "inputnode.h"
#include "ui_mainwindow.h"

#include "filteredconsole.h"
#include "serialnode.h"
#include "dialogwindow.h"

#include "visualnodebase.h"
#include "itemlist.h"
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
    void initActionsConnections();

private:
    SerialNode* serialNode = nullptr;
    Ui::MainWindow *m_ui = nullptr;
    FilteredConsole *filteredConsole = nullptr;
    NodeScene *nodeScene = nullptr;
    ItemList* itemsList = nullptr;
    QTimer *UiUpdatetimer = nullptr;
};
