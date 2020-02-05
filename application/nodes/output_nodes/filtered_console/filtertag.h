#pragma once
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

#include "json_defs.h"

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
    QString tagName;
    int tagIndex;
    QList<TagOption*> options;
    bool visible = true;

    Tag(QString tagName, int tagIndex)
        :tagName(tagName),tagIndex(tagIndex){}
    Tag(QJsonObject &jsonTag)
    {
        tagName = jsonTag.find(JSON_FILTEREDCONSOLE_TAG_NAME)->toString();
        visible = jsonTag.find(JSON_FILTEREDCONSOLE_TAG_VISIBLE)->toBool();
        tagIndex = jsonTag.find(JSON_FILTEREDCONSOLE_TAG_INDEX)->toInt();

        QJsonArray optionJson = jsonTag.find(JSON_FILTEREDCONSOLE_OPTIONS)->toArray();
        QJsonArray::iterator it;
        for (it = optionJson.begin(); it != optionJson.end(); it++) {
            QJsonObject tagJson = it->toObject();

            QString optionName = tagJson.find(JSON_FILTEREDCONSOLE_OPTION_TAGNAME)->toString();
            bool enabled = tagJson.find(JSON_FILTEREDCONSOLE_OPTION_ENABLED)->toBool();
            TagOption *newOption = new TagOption(optionName, enabled);
            options.append(newOption);
        }
    }
    QJsonObject* serialize()
    {
        QJsonObject* jsonObject = new QJsonObject;
        jsonObject->insert(JSON_FILTEREDCONSOLE_TAG_NAME, tagName);
        jsonObject->insert(JSON_FILTEREDCONSOLE_TAG_VISIBLE, visible);
        jsonObject->insert(JSON_FILTEREDCONSOLE_TAG_INDEX, tagIndex);

        QJsonArray optionsJsonArray;
        QListIterator<TagOption*> iterator(options);
        while(iterator.hasNext())
        {
            TagOption* option = iterator.next();
            QJsonObject jsonOption;
            jsonOption.insert(JSON_FILTEREDCONSOLE_OPTION_TAGNAME,option->name);
            jsonOption.insert(JSON_FILTEREDCONSOLE_OPTION_ENABLED,option->enabled);
            optionsJsonArray.append(jsonOption);
        }

        jsonObject->insert(JSON_FILTEREDCONSOLE_OPTIONS,optionsJsonArray);
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
