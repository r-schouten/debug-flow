#pragma once
#include <QSerialPort>
#include <QMessageBox>

#include "outputnode.h"
#include "serialsettings.h"

class SerialNode : public QObject, public OutputNode
{
    Q_OBJECT
public:
    SerialNode();
    ~SerialNode();

    NodeSettingsBase *getNodeSettings();

    SerialSettings* settings = nullptr;

private:
    QSerialPort *m_serial = nullptr;
public slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
signals:
    void SerialPortError(QSerialPort::SerialPortError error);

};

