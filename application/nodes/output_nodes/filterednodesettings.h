#pragma once
#include <QList>

#include "nodesettingsbase.h"

#define DEFAULT_CONSOLE_BLOCK_COUNT 10000
struct TagOption
{
    TagOption(QString name,bool enabled)
        :name(name),enabled(enabled){}
    QString name;
    bool enabled = false;
};

class Tag
{
public:
    Tag(QString tagName)
        :tagName(tagName){}
    QString tagName;
    QList<TagOption*> options;
    bool visible = true;
    TagOption* getOption(QString OptionName)
    {
        QListIterator<TagOption*> iterator(options);
        while(iterator.hasNext())
        {
            TagOption* option = iterator.next();
            if(option->name.compare(OptionName) == 0)
            {
                return option;
            }
        }
        return nullptr;
    }
};
class FilteredNodeSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    FilteredNodeSettings();

    void addOption(Tag* tag,TagOption* option);
    struct Settings
    {
        QList<Tag*> tags;
        bool filterOnWindow = true;
        bool LineNumbersEnabled = false;
        bool ANSIEnabled = true;
        bool autoScrollEnabled = true;
        //        horizontalScrollComboBox = nullptr;
        int maxLinesComboBox = DEFAULT_CONSOLE_BLOCK_COUNT;

    }nodeSettings;

signals:
    void optionAdded(Tag* tag);
};

