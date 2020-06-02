#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "taggroupbox.h"
class TagsAndOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    TagsAndOptionsWidget(QWidget *parent, QList<Tag *> *tags);
    virtual ~TagsAndOptionsWidget();

    QList<TagGroupbox*> tagGroupboxes;
    QList<Tag *> *tags;
public slots:
    void loadTags();
    void optionAdded(Tag *destinationTag, TagOption *option);
private:
    QVBoxLayout* layout = nullptr;
};

