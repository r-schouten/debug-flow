#include "filterednodesettings.h"

FilteredNodeSettings::FilteredNodeSettings()
{

}

void FilteredNodeSettings::addOption(Tag *tag, TagOption *option)
{
    tag->options.append(option);
    emit optionAdded(tag, option);
    emit settingsChanged();
}

void FilteredNodeSettings::clearConsoleClicked()
{
    emit clearConsole();
}

void FilteredNodeSettings::clearContextClicked()
{
    while(tags.size() > 0)
    {
        delete tags.takeAt(0);
    }
    emit tagsChanged();
    emit settingsChanged();
}
void FilteredNodeSettings::setHorizontalScroll(const HorizontalScrollOptions &value)
{
    horizontalScroll = value;
    emit scrollSettingsChanged();
    emit settingsChanged();
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
    emit settingsChanged();
}

bool FilteredNodeSettings::getFilterOnWindow() const
{
    return filterOnWindow;
}

void FilteredNodeSettings::setFilterOnWindow(bool value)
{
    filterOnWindow = value;
    emit filterOnWindowChanged();
    emit settingsChanged();
}
bool FilteredNodeSettings::getHideContext() const
{
    return hideContext;
}

void FilteredNodeSettings::setHideContext(bool value)
{
    hideContext = value;
    emit settingsChanged();
}

bool FilteredNodeSettings::getANSIEnabled() const
{
    return ANSIEnabled;
}

void FilteredNodeSettings::setANSIEnabled(bool value)
{
    ANSIEnabled = value;
    emit settingsChanged();
}

bool FilteredNodeSettings::getLineNumbersEnabled() const
{
    return LineNumbersEnabled;
}

void FilteredNodeSettings::setLineNumbersEnabled(bool value)
{
    LineNumbersEnabled = value;
    emit settingsChanged();
}

void FilteredNodeSettings::setAutoScrollEnabled(bool value)
{
    autoScrollEnabled = value;
    emit settingsChanged();
}

bool FilteredNodeSettings::getAutoScrollEnabled() const
{
    return autoScrollEnabled;
}


QJsonObject *FilteredNodeSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert(JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED,LineNumbersEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_ANSIENABLED,ANSIEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_AUTO_SCROLL,autoScrollEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_HIDE_CONTEXT,hideContext);

    jsonObject->insert(JSON_FILTEREDCONSOLE_MAX_LINES,maxLines);

    jsonObject->insert(JSON_FILTEREDCONSOLE_H_SCROLL,ScrollOptionsText[(int)horizontalScroll]);
    jsonObject->insert(JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW,filterOnWindow);

    if(handler.saveContext())
    {
        QJsonArray tagsJson;

        QListIterator<Tag*>iterator(tags);
        while(iterator.hasNext())
        {
            Tag* tag = iterator.next();
            QJsonObject* tagJson = tag->serialize();
            tagsJson.append(*tagJson);
            delete tagJson;
        }
        jsonObject->insert(JSON_FILTEREDCONSOLE_TAGS,tagsJson);
    }
    return jsonObject;
}

void FilteredNodeSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    LineNumbersEnabled = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED, jsonObject);
    ANSIEnabled = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_ANSIENABLED, jsonObject);
    autoScrollEnabled = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_AUTO_SCROLL, jsonObject);
    hideContext = handler.findBoolSafe(CLASSNAME, JSON_FILTEREDCONSOLE_HIDE_CONTEXT, jsonObject);

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
    QJsonArray tagsJson = handler.findArraySafe(CLASSNAME, JSON_FILTEREDCONSOLE_TAGS, jsonObject,ErrorLevel::WARNING);
    QJsonArray::iterator it;
    for (it = tagsJson.begin(); it != tagsJson.end(); it++) {
        QJsonObject tagJson = it->toObject();
        tags.append(new Tag(tagJson, handler));
    }
}
