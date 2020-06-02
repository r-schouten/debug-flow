#pragma once
#include <QJsonObject>

#include "nodesettingsbase.h"
#include "json_defs.h"

#include "filtertag.h"
#include "tagandoptionssettings.h"
class ContextFilterSettings: public NodeSettingsBase
{
    Q_OBJECT
public:
    ContextFilterSettings();
    virtual ~ContextFilterSettings();
    QJsonObject *serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    TagAndOptionsSettings* tagAndOptionsSettings = nullptr;

public slots:
    void notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event);
    void optionAdded(Tag* tag,TagOption* option);
    void tagsChanged();
};


