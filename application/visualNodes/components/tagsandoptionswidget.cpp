#include "tagsandoptionswidget.h"

TagsAndOptionsWidget::TagsAndOptionsWidget(QWidget *parent, QList<Tag*> *tags)
    : QWidget(parent), tags(tags)
{
    layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
}

TagsAndOptionsWidget::~TagsAndOptionsWidget()
{
    while(tagGroupboxes.size() > 0) delete tagGroupboxes.takeAt(0);
}
void TagsAndOptionsWidget::loadTags()
{
    while(tagGroupboxes.size() > 0) delete tagGroupboxes.takeAt(0);


    QListIterator<Tag*> tagIterator(*tags);
    while(tagIterator.hasNext())
    {
        Tag* currentTag = tagIterator.next();
        connect(currentTag, SIGNAL(dataChanged(Tag*)), this, SLOT(dataChanged()));
        TagGroupbox* newGroupBox = new TagGroupbox(currentTag);
        tagGroupboxes.append(newGroupBox);
        newGroupBox->loadTag();
        layout->addWidget(newGroupBox);
        this->update();
    }
}
void TagsAndOptionsWidget::optionAdded(Tag* destinationTag, TagOption* option)
{

    TagGroupbox* destinationGroupbox = nullptr;
    if(tagGroupboxes.size() <= destinationTag->tagIndex)
    {
        connect(destinationTag, SIGNAL(dataChanged(Tag*)), this, SLOT(dataChanged()));
        destinationGroupbox = new TagGroupbox(destinationTag);

        tagGroupboxes.append(destinationGroupbox);
        layout->addWidget(destinationGroupbox);
    }
    else {
        destinationGroupbox = tagGroupboxes.at(destinationTag->tagIndex);
    }

    TagOptionItem* item = new TagOptionItem(option);
    item->setText(option->name);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(item->tagOption->enabled? Qt::Checked:Qt::Unchecked, Qt::CheckStateRole);

    destinationGroupbox->itemModel->appendRow(item);
}

void TagsAndOptionsWidget::dataChanged()
{
    emit DataChanged();
}
