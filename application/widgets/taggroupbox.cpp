#include "taggroupbox.h"


TagGroupbox::TagGroupbox(Tag *tag)
    :tag(tag)
{
    this->setTitle(tag->tagName);

    tagList = new QListView();
    tagList->setResizeMode(QListView::Adjust);
    //tagList->setFixedSize(125,125);
    tagList->setSizeAdjustPolicy(QListWidget::AdjustToContents);
    itemModel = new QStandardItemModel();
    tagList->setModel(itemModel);
    layout->addWidget(tagList);

    layout->addStretch(0);
    this->setLayout(layout);

    connect(itemModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(itemChanged(QStandardItem*)));
    connect(tag,SIGNAL(dataChanged(Tag*)),this,SLOT(loadTag()));

}

TagGroupbox::~TagGroupbox()
{
    delete layout;
    delete tagList;
    delete itemModel;
}

void TagGroupbox::loadTag()
{
    itemModel->clear();
    QListIterator<TagOption*> optionIterator(tag->options);
    while(optionIterator.hasNext())
    {
        TagOption* currentOption = optionIterator.next();
        TagOptionItem* item = new TagOptionItem(currentOption);
        item->setText(currentOption->name);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(item->tagOption->enabled? Qt::Checked:Qt::Unchecked, Qt::CheckStateRole);

        itemModel->appendRow(item);
    }
}

void TagGroupbox::itemChanged(QStandardItem *item)
{
    TagOptionItem* option = dynamic_cast<TagOptionItem*>(item);
    if(option)
    {
        option->tagOption->enabled = option->checkState();
        tag->notifyDataChanged();
    }
}
