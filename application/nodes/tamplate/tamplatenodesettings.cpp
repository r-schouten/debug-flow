#include "tamplatenodesettings.h"

TamplateNodeSettings::TamplateNodeSettings(DbgLogger *dbgLogger)
    :NodeSettingsBase(dbgLogger)
{

}

QJsonObject *TamplateNodeSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    return jsonObject;
}

void TamplateNodeSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}

void TamplateNodeSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"tamplate node settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
}

