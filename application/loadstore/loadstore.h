#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "visualnodebase.h"
#include "nodescene.h"

#include "visualfilteredconsole.h"
#include "visualserialnode.h"
#include "visualcontextfilter.h"
#include "visualtestgeneratornode.h"
#include "visualsimpleconsole.h"

#include "json_defs.h"
#include "serialization_handler.h"
#include "deserialization_handler.h"


class LoadStore : public QObject
{
    Q_OBJECT
public:
    LoadStore(FlowObjects *flowObjects, NodeScene* scene);
    QJsonObject* serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    VisualNodeBase *deserializeNode(QJsonObject &jsonNodeObject, DeserializationHandler &handler);
    VisualConnection *deserializeConnection(QJsonObject &jsonNodeObject, DeserializationHandler &handler);
    static QJsonObject *serializeNode(VisualNodeBase *node, SerializationHandler &handler);
private:
    FlowObjects* flowObjects = nullptr;
    NodeScene* scene = nullptr;

    VisualNodeBase *constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler);
};

