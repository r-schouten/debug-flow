#include "filterednodesettings.h"

FilteredNodeSettings::FilteredNodeSettings()
{

}

void FilteredNodeSettings::addOption(Tag *tag, TagOption *option)
{
    tag->options.append(option);
    emit optionAdded(tag, option);
}

void FilteredNodeSettings::setHorizontalScroll(const HorizontalScrollOptions &value)
{
    horizontalScroll = value;
    emit scrollSettingsChanged();
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
}

bool FilteredNodeSettings::getFilterOnWindow() const
{
    return filterOnWindow;
}

void FilteredNodeSettings::setFilterOnWindow(bool value)
{
    filterOnWindow = value;
    emit filterOnWindowChanged();
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
}

QJsonObject *FilteredNodeSettings::serialize(SerializationSettings_t &serialisationSettings, SerializationErrorLog &serialisationErrorLog)
{
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert(JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED,LineNumbersEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_ANSIENABLED,ANSIEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_AUTO_SCROLL,autoScrollEnabled);
    jsonObject->insert(JSON_FILTEREDCONSOLE_HIDE_CONTEXT,hideContext);

    jsonObject->insert(JSON_FILTEREDCONSOLE_MAX_LINES,maxLines);

    jsonObject->insert(JSON_FILTEREDCONSOLE_H_SCROLL,ScrollOptionsText[(int)horizontalScroll]);
    jsonObject->insert(JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW,filterOnWindow);

    if(serialisationSettings.serializeContext)
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

void FilteredNodeSettings::deserialize(QJsonObject &jsonObject)
{
    LineNumbersEnabled = jsonObject.find(JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED)->toBool();
    ANSIEnabled = jsonObject.find(JSON_FILTEREDCONSOLE_ANSIENABLED)->toBool();
    autoScrollEnabled = jsonObject.find(JSON_FILTEREDCONSOLE_AUTO_SCROLL)->toBool();
    hideContext = jsonObject.find(JSON_FILTEREDCONSOLE_HIDE_CONTEXT)->toBool();

    maxLines = jsonObject.find(JSON_FILTEREDCONSOLE_MAX_LINES)->toInt();

    filterOnWindow = jsonObject.find(JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW)->toBool();

    QString scrollOption = jsonObject.find(JSON_FILTEREDCONSOLE_H_SCROLL)->toString();
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
        qFatal("[fatal][FilteredNodeSettings] scroll option not found");
    }

    //depending on to the SerializationSettings_t the JSON_FILTEREDCONSOLE_TAGS key is not in the json
    QJsonArray tagsJson = jsonObject.find(JSON_FILTEREDCONSOLE_TAGS)->toArray();
    QJsonArray::iterator it;
    for (it = tagsJson.begin(); it != tagsJson.end(); it++) {
        QJsonObject tagJson = it->toObject();
        tags.append(new Tag(tagJson));
    }
}

