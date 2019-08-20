#pragma once
#include <QSerialPort>

#include "nodesettingsbase.h"
class SerialSettings : public NodeSettingsBase
{
public:
    SerialSettings();
    struct Settings
    {
        bool running = false;
        bool errorOccured = false;
        QString errorString;
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    }nodeSettings;

    Settings settings()
    {
        return nodeSettings;
    }
    void print();
};

