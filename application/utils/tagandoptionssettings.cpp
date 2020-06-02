#include "tagandoptionssettings.h"

TagAndOptionsSettings::TagAndOptionsSettings()
{

}
void TagAndOptionsSettings::addOption(Tag *tag, TagOption *option)
{
    tag->options.append(option);
    emit optionAdded(tag, option);
    notifySettingsChanged(DATA_VALID, SAVE, NODE);
}
bool TagAndOptionsSettings::getHideContext() const
{
    return hideContext;
}

void TagAndOptionsSettings::setHideContext(bool value)
{
    hideContext = value;
    notifySettingsChanged(DATA_INVALID, SAVE, PROPERIES);
}
bool TagAndOptionsSettings::getANSIEnabled() const
{
    return ANSIEnabled;
}

void TagAndOptionsSettings::setANSIEnabled(bool value)
{
    ANSIEnabled = value;
    notifySettingsChanged(DATA_INVALID, SAVE, PROPERIES);
}
QJsonObject *TagAndOptionsSettings::serialize(SerializationHandler &handler)
{
    return nullptr;
}

void TagAndOptionsSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}

void TagAndOptionsSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{

}
