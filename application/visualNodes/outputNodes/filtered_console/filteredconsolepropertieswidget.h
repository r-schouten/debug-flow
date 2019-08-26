#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QStandardItemModel>

#include "filterednodesettings.h"
#include "propertywidgetbase.h"


class TagGroupbox :public QGroupBox
{
public:
    TagGroupbox(Tag* tag)
        :tag(tag){
        //this->setTitle(tag->tagName);

        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setVerticalStretch(1);
        this->setSizePolicy(sizePolicy);

        comboBox = new QComboBox();
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        itemModel = new QStandardItemModel();
        comboBox->setModel(itemModel);
        layout->addWidget(comboBox);

        showTagCheckBox = new QCheckBox;
        showTagCheckBox->setChecked(false);
        showTagCheckBox->setText("hide");
        layout->addWidget(showTagCheckBox);


        layout->addStretch(0);
        this->setLayout(layout);

        comboBox->show();
    }
    ~TagGroupbox()
    {
        while(options.size()>0) options.removeAt(0);
        if(itemModel) delete itemModel;
        if(comboBox) delete comboBox;
        if(layout) delete layout;
        if(showTagCheckBox)delete showTagCheckBox;
    }
    Tag* tag = nullptr;
    QList<QStandardItem*> options;
    QStandardItemModel* itemModel = nullptr;
    QComboBox* comboBox = nullptr;
    QCheckBox* showTagCheckBox = nullptr;
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
    void optionAdded(Tag *tag);
private:
    FilteredNodeSettings* settings = nullptr;
    void loadTag(TagGroupbox *tagGroupbox);

    QVBoxLayout* layout = nullptr;
    QWidget* container = nullptr;
    QFormLayout* containerLayout = nullptr;

    QCheckBox* filterOnWindowCheckbox = nullptr;
    QCheckBox* LineNumbersCheckbox = nullptr;
    QCheckBox*ANSICheckbox = nullptr;
    QCheckBox* autoScrollCheckbox = nullptr;
    QComboBox* horizontalScrollComboBox = nullptr;
    QComboBox* maxLinesComboBox = nullptr;
};

