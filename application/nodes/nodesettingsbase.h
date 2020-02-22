#pragma once
#include <QObject>

#include "serializable.h"

#include "nodebase.h"

class NodeSettingsBase : public QObject, public Serializable
{
    Q_OBJECT
public:
    NodeSettingsBase();
    virtual void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler) = 0;
signals:
    void settingsChanged(NodeSettingsBase* nodeSettings);
};

