#pragma once

#include <iostream>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>

#include "inputnode.h"
#include "ui_mainwindow.h"

#include "filteredconsole.h"
#include "serialnode.h"
#include "filteredterminal.h"
#include "dialogwindow.h"
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

private slots:
    void about();


private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);
    SerialNode* serialNode = nullptr;
    Ui::MainWindow *m_ui = nullptr;
    QLabel *m_status = nullptr;
    FilteredConsole *filteredConsole = nullptr;
    FilteredTerminal *terminal = nullptr;

};
