#pragma once
#include <QList>

#include "nodesettingsbase.h"

#define DEFAULT_CONSOLE_BLOCK_COUNT 10000


enum class HorizontalScrollOptions:int{
    scrollbar=0,
    ignore=1,
    newline=2
};
struct TagOption
{
    TagOption(QString name,bool enabled)
        :name(name),enabled(enabled){}
    QString name;
    bool enabled = false;
};

class Tag: public QObject
{
    Q_OBJECT
public:
    Tag(QString tagName, int tagIndex)
        :tagName(tagName),tagIndex(tagIndex){}
    QString tagName;
    int tagIndex;
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
    void notifyDataChanged()
    {
        emit dataChanged(this);
    }
signals:
    void dataChanged(Tag* tag);
};
class FilteredNodeSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    FilteredNodeSettings();
    void addOption(Tag* tag,TagOption* option);

    void setHorizontalScroll(const HorizontalScrollOptions &value);
    HorizontalScrollOptions getHorizontalScroll() const;

    int getMaxLinesComboBox() const;
    void setMaxLinesComboBox(int value);

    QList<Tag*> tags;
    bool filterOnWindow = true;
    bool LineNumbersEnabled = false;
    bool ANSIEnabled = true;
    bool autoScrollEnabled = true;
    bool hideContext = false;

private:
    int maxLinesComboBox = DEFAULT_CONSOLE_BLOCK_COUNT;
    HorizontalScrollOptions horizontalScroll = HorizontalScrollOptions::scrollbar;

signals:
    void optionAdded(Tag* tag,TagOption* option);
};

