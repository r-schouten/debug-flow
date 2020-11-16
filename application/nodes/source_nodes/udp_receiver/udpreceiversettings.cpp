#include "udpreceiversettings.h"


UdpReceiverSettings::UdpReceiverSettings(DbgLogger *dbgLogger)
     :NodeSettingsBase(dbgLogger)
{

}
QJsonObject *UdpReceiverSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    return jsonObject;
}

void UdpReceiverSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}
void UdpReceiverSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"UDP receiver node settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
}

bool UdpReceiverSettings::getEnabled() const
{
    return enabled;
}

void UdpReceiverSettings::setEnabled(bool value)
{
    enabled = value;
}

QString UdpReceiverSettings::getIpAdress() const
{
    return ipAdress;
}

void UdpReceiverSettings::setIpAdress(const QString &value)
{
    ipAdress = value;
}

int UdpReceiverSettings::getUdp_port() const
{
    return udp_port;
}

void UdpReceiverSettings::setUdp_port(int value)
{
    udp_port = value;
}
