#include "contextfiltersettings.h"

ContextFilterSettings::ContextFilterSettings(DbgLogger* dbgLogger)
    :NodeSettingsBase(dbgLogger)
{
    tagAndOptionsSettings = new TagAndOptionsSettings();
    connect(tagAndOptionsSettings, SIGNAL(optionAdded(Tag*,TagOption*)),this, SLOT(optionAdded(Tag*,TagOption*)));
    connect(tagAndOptionsSettings, SIGNAL(tagsChanged()),this, SLOT(tagsChanged()));
    connect(tagAndOptionsSettings, SIGNAL(settingsChanged(DataValid,SaveSettings, SettingsChangeSource, int)), SLOT(notifySettingsChanged(DataValid,SaveSettings, SettingsChangeSource, int)));
}

ContextFilterSettings::~ContextFilterSettings()
{
    delete tagAndOptionsSettings;
}

QJsonObject *ContextFilterSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert(JSON_TAGS_HIDE_CONTEXT,tagAndOptionsSettings->getHideContext());

    if(handler.saveContext())
    {
        QJsonArray* tagsJson = tagAndOptionsSettings->serialize(handler);
        jsonObject->insert(JSON_TAGS,*tagsJson);
        delete tagsJson;
    }
    return jsonObject;
}

void ContextFilterSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    tagAndOptionsSettings->setHideContext(handler.findBoolSafe(CLASSNAME, JSON_TAGS_HIDE_CONTEXT, jsonObject));

    QJsonArray tagsJson = handler.findArraySafe(CLASSNAME, JSON_TAGS, jsonObject,ErrorLevel::WARNING);
    if(!tagsJson.isEmpty())
    {
        tagAndOptionsSettings->deserialize(tagsJson, handler);

    }
}

void ContextFilterSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug("ContextFilterSettings",__FUNCTION__,"contextfilter node settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
    if(dataValid == DATA_INVALID)
    {
        dbgLogger->debug("ContextFilterSettings",__FUNCTION__,"data invalid");
        emit notifyDataInvalid();
    }
}

void ContextFilterSettings::optionAdded(Tag *tag, TagOption *option)
{
    Q_UNUSED(tag);
    Q_UNUSED(option);
    notifySettingsChanged(DATA_VALID, SAVE, NODE, 0);
}

void ContextFilterSettings::tagsChanged()
{
    notifySettingsChanged(DATA_INVALID, SAVE, NODE, 0);
}

MergeMode_t ContextFilterSettings::getMergeMode() const
{
    return mergeMode;
}

void ContextFilterSettings::setMergeMode(const MergeMode_t &value)
{
    mergeMode = value;
}
