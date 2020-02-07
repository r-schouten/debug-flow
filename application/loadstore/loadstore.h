#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "nodescene.h"

#include "visualnodebase.h"
#include "flowdata.h"

#include "visualfilteredconsole.h"

#include "json_defs.h"
#include "serialization_settings.h"
#include "deserialization_settings.h"
#include "serialization_error_log.h"
class LoadStore : public QObject
{
    Q_OBJECT
public:
    LoadStore(FlowData* flowData, NodeScene* scene);
    QJsonObject* serialize(SerializationSettings_t &serialisationSettings, SerializationErrorLog &serialisationErrorLog);
    void deserialize(QJsonObject &jsonObject, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &deserialisationErrorLog);
    void deserializeNode(QJsonObject &jsonNodeObject, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &deserialisationErrorLog);
private:
    FlowData* flowData = nullptr;
    NodeScene* scene = nullptr;

    VisualNodeBase *constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog);
};

