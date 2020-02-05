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

    jsonObject->insert("ScrollOptionsText",ScrollOptionsText[(int)horizontalScroll]);
    jsonObject->insert("filterOnWindow",filterOnWindow);
    jsonObject->insert("tags",tagsJson);
    return jsonObject;
}

void FilteredNodeSettings::deserialize(QJsonObject *jsonObject)
{

}

