#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "taggroupbox.h"
class TagsAndOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    TagsAndOptionsWidget(QWidget *parent, QVector<Tag *> *tags);
    virtual ~TagsAndOptionsWidget();

    QList<TagGroupbox*> tagGroupboxes;
    QVector<Tag *> *tags;
public slots:
    void loadTags();
    void optionAdded(Tag *destinationTag, TagOption *option);
    void dataChanged();
private:
    QVBoxLayout* layout = nullptr;
signals:
    void DataChanged();
};

