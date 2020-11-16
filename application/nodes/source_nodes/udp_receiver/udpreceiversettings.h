#pragma once

#include <QJsonObject>

#include "nodesettingsbase.h"

class UdpReceiverSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    UdpReceiverSettings(DbgLogger* dbgLogger);

    QJsonObject *serialize(SerializationHandler &handler);

    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    void notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event);


    bool getEnabled() const;
    void setEnabled(bool value);

    QString getIpAdress() const;
    void setIpAdress(const QString &value);

    int getUdp_port() const;
    void setUdp_port(int value);

private:
    bool enabled = true;
    int udp_port = 4230;
    QString ipAdress;

signals:
};
