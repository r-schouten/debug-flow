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
#include "tag-option-item.h"
#include "taggroupbox.h"
#include "tagsandoptionswidget.h"
class FilteredConsolePropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    FilteredConsolePropertiesWidget(QWidget *parent, DbgLogger* dbgLogger, FilteredNodeSettings *settings);
    virtual ~FilteredConsolePropertiesWidget();

public slots:
    void hideContextStateChanged();
    void horizontalScrollIndexChanged(int index);
    void maxLinesIndexChanged(int index);
    void filterOnWindowStateChanged();
    void SideLineOptionsChanged();
    void ANSIStateChanged();
    void autoScrollStateChanged();
    void contextSettingsChanged();

private:

    FilteredNodeSettings* settings = nullptr;

    QVBoxLayout* layout = nullptr;
    QWidget* formContainer = nullptr;
    QFormLayout* containerLayout = nullptr;
    TagsAndOptionsWidget* tagContainer = nullptr;

    QCheckBox* filterOnWindowCheckbox = nullptr;
    QComboBox* sideLineOptionsCombobox = nullptr;
    QCheckBox* hideContextCheckbox = nullptr;

    QCheckBox*ANSICheckbox = nullptr;
    QCheckBox* autoScrollCheckbox = nullptr;
    QComboBox* horizontalScrollComboBox = nullptr;
    QComboBox* maxLinesComboBox = nullptr;
};

