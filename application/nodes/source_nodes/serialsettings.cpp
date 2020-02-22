#include "serialsettings.h"

SerialSettings::SerialSettings()
{
    nodeSettings.running = false;
    nodeSettings.baudRate = 9600;

    nodeSettings.dataBits = QSerialPort::Data8;

    nodeSettings.parity = QSerialPort::NoParity;

    nodeSettings.stopBits = QSerialPort::OneStop;

    nodeSettings.flowControl = QSerialPort::NoFlowControl;
}

void SerialSettings::print()
{
    qDebug() << "--Serial settings--";
    qDebug() << "port :" << nodeSettings.name;
    qDebug() << "baudrate :" << nodeSettings.baudRate;
    qDebug() << "parity : " << nodeSettings.parity;
}

QJsonObject *SerialSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_SERIAL_RUNNING,nodeSettings.running);
    jsonObject->insert(JSON_SERIAL_NAME,nodeSettings.name);
    jsonObject->insert(JSON_SERIAL_BAUDRATE,nodeSettings.baudRate);
    jsonObject->insert(JSON_SERIAL_DATABITS,(int)nodeSettings.dataBits);
    jsonObject->insert(JSON_SERIAL_PARITY,(int)nodeSettings.parity);
    jsonObject->insert(JSON_SERIAL_STOPBITS,(int)nodeSettings.stopBits);
    jsonObject->insert(JSON_SERIAL_FLOWCONTROL,(int)nodeSettings.flowControl);

    return jsonObject;
}

void SerialSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    nodeSettings.name = handler.findStringSafe(CLASSNAME, JSON_SERIAL_NAME, jsonObject);
    nodeSettings.baudRate = handler.findIntSafe(CLASSNAME, JSON_SERIAL_BAUDRATE, jsonObject);
    nodeSettings.dataBits = (QSerialPort::DataBits)handler.findIntSafe(CLASSNAME, JSON_SERIAL_DATABITS, jsonObject);
    nodeSettings.parity = (QSerialPort::Parity)handler.findIntSafe(CLASSNAME, JSON_SERIAL_PARITY, jsonObject);
    nodeSettings.stopBits = (QSerialPort::StopBits)handler.findIntSafe(CLASSNAME, JSON_SERIAL_STOPBITS, jsonObject);
    nodeSettings.flowControl = (QSerialPort::FlowControl)handler.findIntSafe(CLASSNAME, JSON_SERIAL_FLOWCONTROL, jsonObject);
}
