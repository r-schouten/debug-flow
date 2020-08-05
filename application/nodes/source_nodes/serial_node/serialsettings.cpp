#include "serialsettings.h"

SerialSettings::SerialSettings(DbgLogger *dbgLogger)
    :NodeSettingsBase(dbgLogger)
{
    running = false;
    baudRate = 9600;

    dataBits = QSerialPort::Data8;
    parity = QSerialPort::NoParity;
    stopBits = QSerialPort::OneStop;
    flowControl = QSerialPort::NoFlowControl;
}

void SerialSettings::print()
{
    //not tested after change
    dbgLogger->debug(CLASSNAME, __FUNCTION__, "--Serial settings--\nport :%s\nbaudrate: %d\nparity: %d",name.toStdString().c_str(),baudRate,parity);
}

QJsonObject *SerialSettings::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonObject *jsonObject = new QJsonObject();

    jsonObject->insert(JSON_SERIAL_RUNNING,running);
    jsonObject->insert(JSON_SERIAL_NAME,name);
    jsonObject->insert(JSON_SERIAL_BAUDRATE,baudRate);
    jsonObject->insert(JSON_SERIAL_DATABITS,(int)dataBits);
    jsonObject->insert(JSON_SERIAL_PARITY,(int)parity);
    jsonObject->insert(JSON_SERIAL_STOPBITS,(int)stopBits);
    jsonObject->insert(JSON_SERIAL_FLOWCONTROL,(int)flowControl);

    return jsonObject;
}

void SerialSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    name = handler.findStringSafe(CLASSNAME, JSON_SERIAL_NAME, jsonObject);
    baudRate = handler.findIntSafe(CLASSNAME, JSON_SERIAL_BAUDRATE, jsonObject);
    dataBits = (QSerialPort::DataBits)handler.findIntSafe(CLASSNAME, JSON_SERIAL_DATABITS, jsonObject);
    parity = (QSerialPort::Parity)handler.findIntSafe(CLASSNAME, JSON_SERIAL_PARITY, jsonObject);
    stopBits = (QSerialPort::StopBits)handler.findIntSafe(CLASSNAME, JSON_SERIAL_STOPBITS, jsonObject);
    flowControl = (QSerialPort::FlowControl)handler.findIntSafe(CLASSNAME, JSON_SERIAL_FLOWCONTROL, jsonObject);
}

void SerialSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"serial settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
}
