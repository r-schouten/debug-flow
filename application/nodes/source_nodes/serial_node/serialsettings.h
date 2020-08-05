#pragma once
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QJsonObject>

#include "nodesettingsbase.h"

#include "json_defs.h"
enum DataBits {
    Data5 = 5,
    Data6 = 6,
    Data7 = 7,
    Data8 = 8,
    UnknownDataBits = -1
};

enum Parity {
    NoParity = 0,
    EvenParity = 2,
    OddParity = 3,
    SpaceParity = 4,
    MarkParity = 5,
    UnknownParity = -1
};

enum StopBits {
    OneStop = 1,
    OneAndHalfStop = 3,
    TwoStop = 2,
    UnknownStopBits = -1
};

enum FlowControl {
    NoFlowControl,
    HardwareControl,
    SoftwareControl,
    UnknownFlowControl = -1
};
class SerialSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    SerialSettings(DbgLogger* dbgLogger);

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

