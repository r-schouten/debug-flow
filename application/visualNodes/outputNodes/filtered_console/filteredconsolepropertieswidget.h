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
#include "taggroupbox.h"

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

