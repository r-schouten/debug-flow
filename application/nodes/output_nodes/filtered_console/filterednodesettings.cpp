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

QJsonObject *FilteredNodeSettings::serialize()
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
    QJsonObject *jsonObject = new QJsonObject();
    jsonObject->insert("LineNumbersEnabled",LineNumbersEnabled);
    jsonObject->insert("ANSIEnabled",ANSIEnabled);
    jsonObject->insert("autoScrollEnabled",autoScrollEnabled);
    jsonObject->insert("hideContext",hideContext);

    jsonObject->insert("maxlines",maxLines);

    jsonObject->insert("scrollOption",ScrollOptionsText[(int)horizontalScroll]);
    jsonObject->insert("filterOnWindow",filterOnWindow);
    jsonObject->insert("tags",tagsJson);
    return jsonObject;
}

void FilteredNodeSettings::deserialize(QJsonObject &jsonObject)
{
    LineNumbersEnabled = jsonObject.find("LineNumbersEnabled")->toBool();
    ANSIEnabled = jsonObject.find("ANSIEnabled")->toBool();
    autoScrollEnabled = jsonObject.find("autoScrollEnabled")->toBool();
    hideContext = jsonObject.find("hideContext")->toBool();

    maxLines = jsonObject.find("maxlines")->toInt();

    filterOnWindow = jsonObject.find("filterOnWindow")->toBool();

    QString scrollOption = jsonObject.find("scrollOption")->toString();
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


    QJsonArray tagsJson = jsonObject.find(JSON_FILTEREDCONSOLE_TAGS)->toArray();
    QJsonArray::iterator it;
    for (it = tagsJson.begin(); it != tagsJson.end(); it++) {
        QJsonObject tagJson = it->toObject();
        tags.append(new Tag(tagJson));
    }
}

