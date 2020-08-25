#pragma once
#include <QJsonObject>

#include "nodesettingsbase.h"
#include "json_defs.h"

#include "filtertag.h"
#include "tagandoptionssettings.h"

enum MergeMode_t
{
    NO_CONTROL,
    ON_NEW_LINE,
    ON_TIMESTAMP
};

class ContextFilterSettings: public NodeSettingsBase
{
    Q_OBJECT
public:
    ContextFilterSettings(DbgLogger* dbgLogger);
    virtual ~ContextFilterSettings();
    QJsonObject *serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    TagAndOptionsSettings* tagAndOptionsSettings = nullptr;

    MergeMode_t getMergeMode() const;
    void setMergeMode(const MergeMode_t &value);

    QStringList mergeModeString = {"no control", "on newline","on timestamp"};
public slots:
    virtual void notifySettingsChanged(DataValid dataValid = DATA_VALID,SaveSettings saveSettings = SAVE, SettingsChangeSource source = PROPERIES, int event = 0);
    void optionAdded(Tag* tag,TagOption* option);
    void tagsChanged();

private:
    MergeMode_t mergeMode = NO_CONTROL;

};


