#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "visualnodebase.h"
#include "flowdata.h"
#include "nodescene.h"

#include "visualfilteredconsole.h"
#include "visualserialnode.h"

#include "json_defs.h"
#include "serialization_handler.h"
#include "deserialization_handler.h"

class LoadStore : public QObject
{
    Q_OBJECT
public:
    LoadStore(FlowData* flowData, NodeScene* scene);
    QJsonObject* serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    void deserializeNode(QJsonObject &jsonNodeObject, DeserializationHandler &handler);
    VisualConnection *deserializeConnection(QJsonObject &jsonNodeObject, DeserializationHandler &handler);
private:
    FlowData* flowData = nullptr;
    NodeScene* scene = nullptr;

    VisualNodeBase *constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
};

