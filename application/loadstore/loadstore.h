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
#include "serialization_handler.h"
class LoadStore : public QObject
{
    Q_OBJECT
public:
    LoadStore(FlowData* flowData, NodeScene* scene);
    QJsonObject* serialize(SerializationSettings_t &serialisationSettings, SerializationHandler &serialisationErrorLog);
    void deserialize(QJsonObject &jsonObject, SerializationHandler &handler);
    void deserializeNode(QJsonObject &jsonNodeObject, SerializationHandler &handler);
private:
    FlowData* flowData = nullptr;
    NodeScene* scene = nullptr;

    VisualNodeBase *constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, SerializationHandler &handler);
};

