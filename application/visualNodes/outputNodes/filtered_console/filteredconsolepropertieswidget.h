#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QStandardItemModel>

#include "filterednodesettings.h"
#include "propertywidgetbase.h"


class TagGroupbox :public QGroupBox
{
    Q_OBJECT
public:
    TagGroupbox(Tag* tag)
        :tag(tag){
        this->setTitle(tag->tagName);

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
        showTagCheckBox->setChecked(!tag->visible);
        showTagCheckBox->setText("hide");
        layout->addWidget(showTagCheckBox);
        connect(showTagCheckBox,SIGNAL(stateChanged(int)),this,SLOT(showTagStateChanged()));

        layout->addStretch(0);
        this->setLayout(layout);

        comboBox->show();
    }
    ~TagGroupbox()
    {
        while(options.size()>0) options.removeAt(0);
    }
    Tag* tag = nullptr;
    QList<QStandardItem*> options;
    QStandardItemModel* itemModel = nullptr;

public slots:
    void showTagStateChanged()
    {
        tag->visible = !showTagCheckBox->checkState();
    }
private:
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
    void horizontalScrollIndexChanged(int index);
    void maxLinesIndexChanged(int index);
    void filterOnWindowStateChanged();
    void lineNumbersStateChanged();
    void ANSIStateChanged();
    void autoScrollStateChanged();
private:
    FilteredNodeSettings* settings = nullptr;
    void loadTag(TagGroupbox *tagGroupbox);

    QVBoxLayout* layout = nullptr;
    QWidget* container = nullptr;
    QFormLayout* containerLayout = nullptr;

    QCheckBox* filterOnWindowCheckbox = nullptr;
    QCheckBox* lineNumbersCheckbox = nullptr;
    QCheckBox*ANSICheckbox = nullptr;
    QCheckBox* autoScrollCheckbox = nullptr;
    QComboBox* horizontalScrollComboBox = nullptr;
    QComboBox* maxLinesComboBox = nullptr;
};

