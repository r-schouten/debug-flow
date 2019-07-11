#pragma once

#include <iostream>
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>

#include "inputnode.h"
#include "ui_mainwindow.h"
#include "filteredconsole.h"
#include "settingsdialog.h"
#include "circularbuffer.h"
#include "serialnode.h"
QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class FilteredConsole;
class SettingsDialog;

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
    SettingsDialog *m_settings = nullptr;

};
