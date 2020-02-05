#pragma once
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

#include "nodesettingsbase.h"

#define DEFAULT_CONSOLE_BLOCK_COUNT 10000

//waring, when changing to enum also change the serialization an deserialisation
static QString ScrollOptionsText[] = {"scrollbar","ignore","newline"};
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

    QJsonObject* serialize()
    {
        QJsonObject* jsonObject = new QJsonObject;
        jsonObject->insert("name",tagName);
        jsonObject->insert("visible",visible);
        jsonObject->insert("index",tagIndex);

        QJsonArray optionsJsonArray;
        QListIterator<TagOption*> iterator(options);
        while(iterator.hasNext())
        {
            TagOption* option = iterator.next();
            QJsonObject jsonOption;
            jsonOption.insert("tagName",option->name);
            jsonOption.insert("enabled",option->enabled);
            optionsJsonArray.append(jsonOption);
        }

        jsonObject->insert("options",optionsJsonArray);
        return jsonObject;
    }
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

    int getMaxLines() const;
    void setMaxLinesComboBox(int value);

    QList<Tag*> tags;
    bool LineNumbersEnabled = false;
    bool ANSIEnabled = true;
    bool autoScrollEnabled = true;
    bool hideContext = false;

    bool getFilterOnWindow() const;
    void setFilterOnWindow(bool value);

    QJsonObject *serialize();
    void deserialize(QJsonObject &jsonObject);
private:
    int maxLines = DEFAULT_CONSOLE_BLOCK_COUNT;
    HorizontalScrollOptions horizontalScroll = HorizontalScrollOptions::scrollbar;
    bool filterOnWindow = true;

signals:
    void optionAdded(Tag* tag,TagOption* option);
    void clearConsole();
    void tagsChanged();
    void maxLinesChanged();
    void scrollSettingsChanged();
    void filterOnWindowChanged();
public slots:
    void clearConsoleClicked();
    void clearContextClicked();
};

