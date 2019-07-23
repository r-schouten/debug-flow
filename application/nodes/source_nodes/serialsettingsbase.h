#pragma once
#include <QSerialPort>

#include "nodesettingsbase.h"
class SerialSettingsBase : public NodeSettingsBase
{
public:
    SerialSettingsBase();
    struct Settings
    {
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

