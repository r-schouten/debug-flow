#pragma once
#include "outputnode.h"

#include <QSerialPort>
#include <QMessageBox>
#include "settingsdialog.h"

class SerialNode : public OutputNode, public QObject
{
public:
    SerialNode(SettingsDialog *settingDialog);
public slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);
private:
    QSerialPort *m_serial = nullptr;
    SettingsDialog* m_settings;
};

