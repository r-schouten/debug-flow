#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QListView>
#include <QListWidget>
#include <QPushButton>
#include <QStandardItemModel>

#include "taggroupbox.h"

#include "propertywidgetbase.h"
#include "contextfiltersettings.h"
#include "tagsandoptionswidget.h"
class VisualContextFilterPropertiesWidget : public PropertyWidgetBase
{
public:
    VisualContextFilterPropertiesWidget(QWidget *parent, ContextFilterSettings* _settings);
    ~VisualContextFilterPropertiesWidget();
protected:
    ContextFilterSettings* settings = nullptr;
    QList<TagGroupbox*> tagGroupboxes;

private:
    QVBoxLayout* layout = nullptr;
    TagsAndOptionsWidget* tagsWidget = nullptr;
};
