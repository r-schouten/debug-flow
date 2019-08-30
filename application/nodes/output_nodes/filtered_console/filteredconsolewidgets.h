#pragma once

#include <QStandardItemModel>
#include <filterednodesettings.h>


class TagOptionItem: public QStandardItem
{
public:
    TagOptionItem(TagOption* option)
        :tagOption(option){}
    TagOption* tagOption = nullptr;
};
