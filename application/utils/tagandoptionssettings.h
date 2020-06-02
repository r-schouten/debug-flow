#pragma once

#include <QJsonObject>

#include "nodesettingsbase.h"
#include "filtertag.h"
class TagAndOptionsSettings: public QObject
{
    Q_OBJECT
public:
    explicit TagAndOptionsSettings();

    void addOption(Tag* tag,TagOption* option);

    bool getHideContext() const;
    void setHideContext(bool value);

    bool getANSIEnabled() const;
    void setANSIEnabled(bool value);

    QJsonArray *serialize(SerializationHandler &handler);
    void deserialize(QJsonArray &jsonArray, DeserializationHandler &handler);
    void notifySettingsChanged(DataValid dataValid = DATA_VALID,SaveSettings saveSettings = SAVE, SettingsChangeSource source = PROPERIES, int event = 0);

    QList<Tag*> tags;
private:
    bool hideContext = false;
    bool ANSIEnabled = true;

signals:
    void optionAdded(Tag* tag,TagOption* option);
    void tagsChanged();




};

