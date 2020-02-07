#include "loadstore.h"

LoadStore::LoadStore(FlowData* flowData, NodeScene* scene)
    :flowData(flowData),scene(scene)
{

}
QJsonObject *LoadStore::serialize(SerializationHandler &handler)
{
    QJsonArray allObjectsJson;
    QListIterator<VisualConnection*>iterator(flowData->connections);
    while(iterator.hasNext())
    {
        VisualConnection* connection = iterator.next();

    }
    QListIterator<VisualNodeBase*>iterator2(flowData->nodes);
    while(iterator2.hasNext())
    {
        VisualNodeBase* node = iterator2.next();

        QJsonObject* derivedJson = node->serialize(handler);
        QJsonObject* baseJson = node->serializeBase(handler);
        if(node->getNode()->getNodeSettings() == nullptr)
        {
            handler.logError(CLASSNAME, "node->getNode()->getNodeSettings() == nullptr");
        }
        QJsonObject* nodeSettingsJson = node->getNode()->getNodeSettings()->serialize(handler);

        QJsonObject jsonObject;
        jsonObject.insert(JSON_DERIVED, *derivedJson);
        jsonObject.insert(JSON_BASE, *baseJson);
        jsonObject.insert(JSON_NODE_SETTINGS, *nodeSettingsJson);
        jsonObject.insert(JSON_CONNECTIONS, "nullptr");

        allObjectsJson.append(jsonObject);

        delete derivedJson;
        delete baseJson;
        delete nodeSettingsJson;
    }
    QJsonObject *completeNodeJson = new QJsonObject;
    completeNodeJson->insert(JSON_NODES,allObjectsJson);
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
        scene->addItem(newNode);
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
    return newNode;
}
