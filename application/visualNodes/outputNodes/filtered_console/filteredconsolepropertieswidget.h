#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QListView>
#include <QListWidget>
#include <QPushButton>
#include <QStandardItemModel>

#include "filterednodesettings.h"
#include "propertywidgetbase.h"
#include "filteredconsolewidgets.h"

class TagGroupbox :public QGroupBox
{
    Q_OBJECT
public:
    TagGroupbox(Tag* tag)
        :tag(tag){
        this->setTitle(tag->tagName);

        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        //sizePolicy.setVerticalStretch(1);
        this->setSizePolicy(sizePolicy);

        comboBox = new QListView();
        //comboBox->setSizePolicy(sizePolicy);
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
    ~TagGroupbox()
    {
        delete layout;
        delete comboBox;
        delete itemModel;
    }

    Tag* tag = nullptr;
    QStandardItemModel* itemModel = nullptr;

public slots:
    void loadTag()
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
    void itemChanged(QStandardItem *item)
    {
        TagOptionItem* option = dynamic_cast<TagOptionItem*>(item);
        if(option)
        {
            option->tagOption->enabled = option->checkState();
            tag->notifyDataChanged();
        }
    }

private:
    QListView* comboBox = nullptr;
    QVBoxLayout* layout = new QVBoxLayout;
};

class FilteredConsolePropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    FilteredConsolePropertiesWidget(QWidget *parent, FilteredNodeSettings *settings);
    ~FilteredConsolePropertiesWidget();
    QList<TagGroupbox*> tagGroupboxes;
public slots:
    void optionAdded(Tag *tag, TagOption *option);
    void hideContextStateChanged();
    void horizontalScrollIndexChanged(int index);
    void maxLinesIndexChanged(int index);
    void filterOnWindowStateChanged();
    void lineNumbersStateChanged();
    void ANSIStateChanged();
    void autoScrollStateChanged();
private slots:
    void loadTags();
private:

    FilteredNodeSettings* settings = nullptr;

    QVBoxLayout* layout = nullptr;
    QWidget* container = nullptr;
    QFormLayout* containerLayout = nullptr;

    QCheckBox* filterOnWindowCheckbox = nullptr;
    QCheckBox* lineNumbersCheckbox = nullptr;
    QCheckBox* hideContextCheckbox = nullptr;

    QCheckBox*ANSICheckbox = nullptr;
    QCheckBox* autoScrollCheckbox = nullptr;
    QComboBox* horizontalScrollComboBox = nullptr;
    QComboBox* maxLinesComboBox = nullptr;
};

