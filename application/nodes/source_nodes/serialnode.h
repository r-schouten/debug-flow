#pragma once
#include "outputnode.h"

#include <QSerialPort>
#include <QMessageBox>
#include "serialsettingsbase.h"
class SerialNode : public OutputNode, public QObject
{
public:
    SerialNode();
public slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    SerialSettingsBase* settings = nullptr;

private:
    QSerialPort *m_serial = nullptr;
};

