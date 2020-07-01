#include "filterednodesettings.h"

FilteredNodeSettings::FilteredNodeSettings(DbgLogger* dbgLogger)
    :NodeSettingsBase(dbgLogger)
{
    tagAndOptionSettings = new TagAndOptionsSettings();
}

FilteredNodeSettings::~FilteredNodeSettings()
{
    delete tagAndOptionSettings;
}


void FilteredNodeSettings::clearConsoleClicked()
{
    emit clearConsole();
}

void FilteredNodeSettings::clearContextClicked()
{
    while(tagAndOptionSettings->tags.size() > 0)
    {
        delete tagAndOptionSettings->tags.takeAt(0);
    }
    emit tagAndOptionSettings->tagsChanged();
    notifySettingsChanged(DATA_VALID, SAVE, PROPERIES);
}
void FilteredNodeSettings::setHorizontalScroll(const HorizontalScrollOptions &value)
{
    horizontalScroll = value;
    emit scrollSettingsChanged();
    notifySettingsChanged(DATA_VALID, SAVE, PROPERIES);
}

HorizontalScrollOptions FilteredNodeSettings::getHorizontalScroll() const
{
    return horizontalScroll;
}

int FilteredNodeSettings::getMaxLines() const
{
    return maxLines;
}

void FilteredNodeSettings::setMaxLinesComboBox(int value)
{
    maxLines = value;
    emit maxLinesChanged();
    notifySettingsChanged(DATA_VALID, SAVE, PROPERIES);
}

bool FilteredNodeSettings::getFilterOnWindow() const
{
    return filterOnWindow;
}

void FilteredNodeSettings::setFilterOnWindow(bool value)
{
    filterOnWindow = value;
    emit filterOnWindowChanged();
    notifySettingsChanged(DATA_VALID, SAVE, PROPERIES);
}

bool FilteredNodeSettings::getLineNumbersEnabled() const
{
    return LineNumbersEnabled;
}

void FilteredNodeSettings::setLineNumbersEnabled(bool value)
{
    LineNumbersEnabled = value;
    notifySettingsChanged(DATA_VALID, SAVE, PROPERIES);
}

void FilteredNodeSettings::setAutoScrollEnabled(bool value)
{
    autoScrollEnabled = value;
    notifySettingsChanged(DATA_VALID, SAVE,PROPERIES);
}

bool FilteredNodeSettings::getAutoScrollEnabled() const
{
    return autoScrollEnabled;
}


QJsonObject *FilteredNodeSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert(JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED,LineNumbersEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_ANSIENABLED,tagAndOptionSettings->getANSIEnabled());
    jsonObject->insert(JSON_FILTEREDCONSOLE_AUTO_SCROLL,autoScrollEnabled);
    jsonObject->insert(JSON_TAGS_HIDE_CONTEXT,tagAndOptionSettings->getHideContext());

    jsonObject->insert(JSON_FILTEREDCONSOLE_MAX_LINES,maxLines);

    jsonObject->insert(JSON_FILTEREDCONSOLE_H_SCROLL,ScrollOptionsText[(int)horizontalScroll]);
    jsonObject->insert(JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW,filterOnWindow);

    if(handler.saveContext())
    {
        QJsonArray tagsJson;

        QListIterator<Tag*>iterator(tagAndOptionSettings->tags);
        while(iterator.hasNext())
        {
            Tag* tag = iterator.next();
            QJsonObject* tagJson = tag->serialize();
            tagsJson.append(*tagJson);
            delete tagJson;
        }
        jsonObject->insert(JSON_TAGS,tagsJson);
    }
    return jsonObject;
}

void FilteredNodeSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    LineNumbersEnabled = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED, jsonObject);
    tagAndOptionSettings->setANSIEnabled(handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_ANSIENABLED, jsonObject));
    autoScrollEnabled = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_AUTO_SCROLL, jsonObject);
    tagAndOptionSettings->setHideContext(handler.findBoolSafe(CLASSNAME, JSON_TAGS_HIDE_CONTEXT, jsonObject));

    maxLines = handler.findIntSafe(CLASSNAME, JSON_FILTEREDCONSOLE_MAX_LINES, jsonObject);

    filterOnWindow = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW, jsonObject);

    QString scrollOption = handler.findStringSafe(CLASSNAME, JSON_FILTEREDCONSOLE_H_SCROLL, jsonObject);
    bool found = false;
    for(int i =0;i<ScrollOptionsText.size();i++)
    {
        if(scrollOption.compare(ScrollOptionsText[i]) == 0)
        {
           horizontalScroll = (HorizontalScrollOptions)i;
           found = true;
        }
    }
    if(!found)
    {
        handler.logError(CLASSNAME,"scroll option not found",jsonObject);
    }

    //depending on to the SerializationSettings_t the JSON_FILTEREDCONSOLE_TAGS key is not in the json
    QJsonArray tagsJson = handler.findArraySafe(CLASSNAME, JSON_TAGS, jsonObject,ErrorLevel::WARNING);
    QJsonArray::iterator it;
    for (it = tagsJson.begin(); it != tagsJson.end(); it++) {
        QJsonObject tagJson = it->toObject();
        tagAndOptionSettings->tags.append(new Tag(tagJson, handler));
    }
}

void FilteredNodeSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug("FilteredNodeSettings",__FUNCTION__,"filtered node settings changed");
    if(saveSettings == SAVE)
    {
        dbgLogger->debug("FilteredNodeSettings",__FUNCTION__,"filtered node settings changed save");
        emit saveAbleChangeOccured();
    }
    if(dataValid == DATA_INVALID)
    {

    }
}
