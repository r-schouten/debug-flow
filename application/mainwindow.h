#pragma once

#include <iostream>
#include <QMainWindow>
#include <QSerialPort>
#include <QLabel>
#include <QMessageBox>

#include "inputnode.h"
#include "ui_mainwindow.h"
#include "filteredconsole.h"
#include "settingsdialog.h"
#include "circularbuffer.h"

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class FilteredConsole;
class SettingsDialog;

class MainWindow : public QMainWindow , public OutputNode
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *m_ui = nullptr;
    QLabel *m_status = nullptr;
    FilteredConsole *filteredConsole = nullptr;
    SettingsDialog *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
};
