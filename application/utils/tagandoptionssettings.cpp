#include "tagandoptionssettings.h"

TagAndOptionsSettings::TagAndOptionsSettings(bool hideTimestamp)
    :hideTimestamp(hideTimestamp)
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

bool TagAndOptionsSettings::getHideTimeStamp() const
{
    return hideTimestamp;
}

void TagAndOptionsSettings::setHideTimeStamp(bool value)
{
    hideTimestamp = value;
}

void TagAndOptionsSettings::setANSIEnabled(bool value)
{
    ANSIEnabled = value;
    notifySettingsChanged(DATA_INVALID, SAVE, PROPERIES);
}
QJsonArray *TagAndOptionsSettings::serialize(SerializationHandler &handler)
{
    Q_UNUSED(handler);
    QJsonArray *tagsJson = new QJsonArray();

    QVectorIterator<Tag*>iterator(tags);
    while(iterator.hasNext())
    {
        Tag* tag = iterator.next();
        QJsonObject* tagJson = tag->serialize();
        tagsJson->append(*tagJson);
        delete tagJson;
    }
    return tagsJson;
}

void TagAndOptionsSettings::deserialize(QJsonArray &jsonArray, DeserializationHandler &handler)
{
    QJsonArray::iterator it;
    for (it = jsonArray.begin(); it != jsonArray.end(); it++) {
        QJsonObject tagJson = it->toObject();
        tags.append(new Tag(tagJson, handler));
    }
}

void TagAndOptionsSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    emit settingsChanged(dataValid, saveSettings, source, event);
}
