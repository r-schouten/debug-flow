#pragma once

#include <QJsonObject>

#include "nodesettingsbase.h"


class ConsistencyCheckerSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    ConsistencyCheckerSettings(DbgLogger* dbgLogger);

    QJsonObject *serialize(SerializationHandler &handler);

    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    void notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event);


    bool getShowAll() const;
    void setShowAll(bool value);

    bool getAutoscroll() const;
    void setAutoscroll(bool value);

private:
    bool enabled = true;

    bool showAll = true;
    bool autoscroll = true;
signals:

};
