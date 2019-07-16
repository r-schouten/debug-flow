#pragma once
#include <QListWidget>


class ItemList
{
private:
    QListView *resourceList;
public:
    ItemList(QListWidget* resourceList);
};

