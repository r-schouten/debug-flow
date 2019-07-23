#include "serialsettingsbase.h"

#include <QSerialPortInfo>

#include <QDebug>
SerialSettingsBase::SerialSettingsBase()
{
    nodeSettings.baudRate = 9600;

    nodeSettings.dataBits = QSerialPort::Data8;

    nodeSettings.parity = QSerialPort::NoParity;

    nodeSettings.stopBits = QSerialPort::OneStop;

    nodeSettings.flowControl = QSerialPort::NoFlowControl;
}

void SerialSettingsBase::print()
{
    qDebug() << "--Serial settings--";
    qDebug() << "port :" << nodeSettings.name;
    qDebug() << "baudrate :" << nodeSettings.baudRate;
    qDebug() << "parity : " << nodeSettings.parity;
}
