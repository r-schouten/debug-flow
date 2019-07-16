#include "itemlist.h"

#include <QListWidget>
#include <QStandardItemModel>

ItemList::ItemList(QListWidget *resourceList)
    :resourceList(resourceList)
{
    for(int i=0;i<20;i++)
    {
        QListWidgetItem* item =  new QListWidgetItem(QIcon(":/images/clear.png"),"test");
        resourceList->setIconSize(QSize(40,40));
        item->setSizeHint(QSize(100,100));
        resourceList->addItem(item);
    }

}
