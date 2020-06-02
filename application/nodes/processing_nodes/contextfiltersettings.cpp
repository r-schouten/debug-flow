#include "contextfiltersettings.h"

ContextFilterSettings::ContextFilterSettings()
{
    tagAndOptionsSettings = new TagAndOptionsSettings();
}

QJsonObject *ContextFilterSettings::serialize(SerializationHandler &handler)
{

}

void ContextFilterSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}

void ContextFilterSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{

}
