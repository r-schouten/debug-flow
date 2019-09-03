#pragma once
#include <QGroupBox>
#include <QListView>
#include <QStandardItem>
#include <QListWidget>
#include <QVBoxLayout>

#include "filterednodesettings.h"
#include "filteredconsolewidgets.h"



class TagGroupbox :public QGroupBox
{
    Q_OBJECT
public:
    TagGroupbox(Tag* tag);
    ~TagGroupbox();

    Tag* tag = nullptr;
    QStandardItemModel* itemModel = nullptr;

public slots:
    void loadTag();
    void itemChanged(QStandardItem *item);

private:
    QListView* tagList = nullptr;
    QVBoxLayout* layout = new QVBoxLayout;
};
