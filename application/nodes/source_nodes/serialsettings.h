#pragma once
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include <QJsonObject>

#include "nodesettingsbase.h"

#include "json_defs.h"
class SerialSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    SerialSettings();

    bool running = false;
    bool errorOccured = false;
    QString errorString;
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;

    void print();

    QJsonObject *serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);

    void notifySettingsChanged(DataValid dataValid = DATA_VALID,SaveSettings saveSettings = SAVE, SettingsChangeSource source = PROPERIES, int event = 0);
signals:
    void SerialErrorOccured();


};

