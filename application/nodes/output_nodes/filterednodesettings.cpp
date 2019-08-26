#include "filterednodesettings.h"

FilteredNodeSettings::FilteredNodeSettings()
{

}

void FilteredNodeSettings::addOption(Tag *tag, TagOption *option)
{
    tag->options.append(option);
    emit optionAdded(tag);
}
