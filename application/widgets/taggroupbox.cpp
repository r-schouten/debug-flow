#include "taggroupbox.h"


TagGroupbox::TagGroupbox(Tag *tag)
    :tag(tag)
{
    this->setTitle(tag->tagName);

    comboBox = new QListView();
    comboBox->setResizeMode(QListView::Adjust);
    comboBox->setFixedSize(125,125);
    comboBox->setSizeAdjustPolicy(QListWidget::AdjustToContents);
    itemModel = new QStandardItemModel();
    comboBox->setModel(itemModel);
    layout->addWidget(comboBox);

    layout->addStretch(0);
    this->setLayout(layout);

    connect(itemModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(itemChanged(QStandardItem*)));
    connect(tag,SIGNAL(dataChanged(Tag*)),this,SLOT(loadTag()));

}

TagGroupbox::~TagGroupbox()
{
    delete layout;
    delete comboBox;
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
