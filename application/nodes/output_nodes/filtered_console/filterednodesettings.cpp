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
}

HorizontalScrollOptions FilteredNodeSettings::getHorizontalScroll() const
{
    return horizontalScroll;
}

int FilteredNodeSettings::getMaxLinesComboBox() const
{
    return maxLinesComboBox;
}

void FilteredNodeSettings::setMaxLinesComboBox(int value)
{
    maxLinesComboBox = value;
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
