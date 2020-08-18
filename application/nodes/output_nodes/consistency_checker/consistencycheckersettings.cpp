#include "consistencycheckersettings.h"

ConsistencyCheckerSettings::ConsistencyCheckerSettings(DbgLogger *dbgLogger)
    :NodeSettingsBase(dbgLogger)
{

}

QJsonObject *ConsistencyCheckerSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    return jsonObject;
}

void ConsistencyCheckerSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}

void ConsistencyCheckerSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"consistency check settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
}

bool ConsistencyCheckerSettings::getShowAll() const
{
    return showAll;
}

void ConsistencyCheckerSettings::setShowAll(bool value)
{
    showAll = value;
}

bool ConsistencyCheckerSettings::getAutoscroll() const
{
    return autoscroll;
}

void ConsistencyCheckerSettings::setAutoscroll(bool value)
{
    autoscroll = value;
}

