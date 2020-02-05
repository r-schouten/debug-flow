#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "nodescene.h"

#include "visualnodebase.h"
#include "flowdata.h"

#include "visualfilteredconsole.h"
class LoadStore
{
public:
    LoadStore(FlowData* flowData, NodeScene* scene);
    QJsonObject* serialize();
    void deserialize(QJsonObject &jsonObject);
    void deserializeNode(QJsonObject &jsonNodeObject);
private:
    FlowData* flowData = nullptr;
    NodeScene* scene = nullptr;

    VisualNodeBase *deserializeDerived(QJsonObject &jsonNodeObject);
    void deserializeSettings(QJsonObject &jsonNodeObject);
};

