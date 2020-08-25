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
    Q_OBJECT

public:
    VisualContextFilterPropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, ContextFilterSettings* _settings);
    virtual ~VisualContextFilterPropertiesWidget();
public slots:
    void contextSettingsChanged();
protected:
    ContextFilterSettings* settings = nullptr;
    QList<TagGroupbox*> tagGroupboxes;

private slots:
    void mergeModeChanged(int index);
private:
    QVBoxLayout* layout = nullptr;
    TagsAndOptionsWidget* tagsWidget = nullptr;

    QComboBox* mergeModeComboBox = nullptr;
};
