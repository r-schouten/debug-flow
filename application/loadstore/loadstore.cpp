#include "loadstore.h"

LoadStore::LoadStore(FlowData* flowData, NodeScene* scene)
    :flowData(flowData),scene(scene)
{

}
QJsonObject *LoadStore::serialize(SerializationHandler &handler)
{
    QJsonArray allConnectionsJson;
    QListIterator<VisualConnection*>iterator(flowData->connections);
    while(iterator.hasNext())
    {
        VisualConnection* connection = iterator.next();
        QJsonObject* connectionJson = connection->serialize(handler);

        if(connectionJson != nullptr)
        {
            allConnectionsJson.append(*connectionJson);

            delete connectionJson;
        }
        else
        {
            handler.logWaring(CLASSNAME, "connection returned a nullptr json object");
        }
    }
    QJsonArray allNodesJson;
    QListIterator<VisualNodeBase*>iterator2(flowData->nodes);
    while(iterator2.hasNext())
    {
        VisualNodeBase* node = iterator2.next();

        QJsonObject* derivedJson = node->serialize(handler);
        QJsonObject* baseJson = node->serializeBase(handler);
        QJsonObject* nodeSettingsJson = nullptr;
        if(node->getNode()->getNodeSettings())
        {
            nodeSettingsJson = node->getNode()->getNodeSettings()->serialize(handler);
        }
        else
        {
            handler.logFatal(CLASSNAME, "node->getNode()->getNodeSettings() == nullptr");
        }

        QJsonObject jsonObject;
        jsonObject.insert(JSON_DERIVED, *derivedJson);
        jsonObject.insert(JSON_BASE, *baseJson);
        jsonObject.insert(JSON_NODE_SETTINGS, *nodeSettingsJson);

        allNodesJson.append(jsonObject);

        delete derivedJson;
        delete baseJson;
        delete nodeSettingsJson;
    }
    QJsonObject *completeNodeJson = new QJsonObject;
    completeNodeJson->insert(JSON_NODES,allNodesJson);
    completeNodeJson->insert(JSON_CONNECTIONS, allConnectionsJson);
    return completeNodeJson;
}



void LoadStore::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{
    QJsonArray nodesJson = handler.findArraySafe(CLASSNAME, JSON_NODES, jsonObject);
    QJsonArray::iterator it;
    for (it = nodesJson.begin(); it != nodesJson.end(); it++) {
        QJsonObject object = it->toObject();
        deserializeNode(object, handler);
    }

    QJsonArray connectionsJson = handler.findArraySafe(CLASSNAME, JSON_CONNECTIONS, jsonObject);
    for (it = connectionsJson.begin(); it != connectionsJson.end(); it++) {
        QJsonObject object = it->toObject();
        deserializeConnection(object, handler);
    }
}
void LoadStore::deserializeNode(QJsonObject &jsonNodeObject, DeserializationHandler &handler)
{
    QJsonObject derivedJson = handler.findObjectSafe(CLASSNAME, JSON_DERIVED, jsonNodeObject);
    QJsonObject baseJson = handler.findObjectSafe(CLASSNAME, JSON_BASE, jsonNodeObject);
    QJsonObject settingsJson = handler.findObjectSafe(CLASSNAME, JSON_NODE_SETTINGS, jsonNodeObject);

    VisualNodeBase* newNode = nullptr;
    newNode = constructNode(baseJson, derivedJson, settingsJson, handler);

    if(newNode)
    {
        scene->addNode(newNode);
    }
    else
    {
        handler.logFatal(metaObject()->className(), "newNode is nullptr", jsonNodeObject);
    }
}

VisualNodeBase *LoadStore::constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationHandler &handler)
{
    VisualNodeBase* newNode = nullptr;
    QString type = handler.findStringSafe(CLASSNAME, JSON_NODE_TYPE, derivedJson);

    if(VisualFilteredConsole::classNameEquals(type))
    {
        newNode = new VisualFilteredConsole(baseJson, derivedJson, settingsJson, handler);
    }
    if(VisualSerialNode::classNameEquals(type))
    {
        newNode = new VisualSerialNode(baseJson, derivedJson, settingsJson, handler);
    }
    return newNode;
}

void LoadStore::deserializeConnection(QJsonObject &jsonNodeObject, DeserializationHandler &handler)
{
    Connector* connector1 = nullptr;
    Connector* connector2 = nullptr;


    int64_t connector1NodeId = handler.findInt64Safe(CLASSNAME, JSON_CONNECTION_CONNECTOR1_NODE_ID, jsonNodeObject);
    int64_t connector2NodeId = handler.findInt64Safe(CLASSNAME, JSON_CONNECTION_CONNECTOR2_NODE_ID, jsonNodeObject);
    QString connector1Name = handler.findStringSafe(CLASSNAME, JSON_CONNECTION_CONNECTOR1_NAME, jsonNodeObject);
    QString connector2Name = handler.findStringSafe(CLASSNAME, JSON_CONNECTION_CONNECTOR2_NAME, jsonNodeObject);

    //search in the node list to find the connected node
    QListIterator<VisualNodeBase*>iterator2(flowData->nodes);
    while(iterator2.hasNext())
    {
        VisualNodeBase* node = iterator2.next();
        if(node->getUniqueId() == connector1NodeId)
        {
            connector1 = node->findConnectorWithName(connector1Name);
            if(connector1 == nullptr) handler.logError(CLASSNAME, "connector 1 name not found",jsonNodeObject);
        }
        if(node->getUniqueId() == connector2NodeId)
        {
            connector2 = node->findConnectorWithName(connector2Name);
            if(connector2 == nullptr) handler.logError(CLASSNAME, "connector 2 name not found",jsonNodeObject);
        }
    }
    if(connector1 && connector2)
    {
        VisualConnection* newConnection = new VisualConnection(connector1, connector2);
        scene->addConnection(newConnection);
    }
    else
    {
        handler.logError(CLASSNAME, "deserializing connection failed",jsonNodeObject);
    }

}
