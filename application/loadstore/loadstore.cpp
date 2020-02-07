#include "loadstore.h"

LoadStore::LoadStore(FlowData* flowData, NodeScene* scene)
    :flowData(flowData),scene(scene)
{

}
QJsonObject *LoadStore::serialize(SerializationSettings_t &serialisationSettings, SerializationErrorLog &errorLog)
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

        QJsonObject* derivedJson = node->serialize(serialisationSettings, errorLog);
        QJsonObject* baseJson = node->serializeBase(serialisationSettings, errorLog);
        if(node->getNode()->getNodeSettings() == nullptr)
        {
            qFatal("[fatal][NodeScene] node->getNode()->getNodeSettings() == nullptr");
        }
        QJsonObject* nodeSettingsJson = node->getNode()->getNodeSettings()->serialize(serialisationSettings, errorLog);

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



void LoadStore::deserialize(QJsonObject &jsonObject, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog)
{
    if(jsonObject.contains(JSON_NODES))
    {
        QJsonArray nodesJson = jsonObject.find(JSON_NODES)->toArray();

        QJsonArray::iterator it;
        for (it = nodesJson.begin(); it != nodesJson.end(); it++) {
            QJsonObject object = it->toObject();
            deserializeNode(object, deserializationSettings, errorLog);
        }
    }
    else
    {
        errorLog.LogWaring(ErrorSource::NODES_BASE, QMetaObject().className(), "element JSON_NODES not found", jsonObject);
    }
}
void LoadStore::deserializeNode(QJsonObject &jsonNodeObject, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog)
{
    //deserialize derived
    QJsonObject::iterator derivedIt = jsonNodeObject.find(JSON_DERIVED);
    if(derivedIt == jsonNodeObject.end()){
        errorLog.LogFatal(ErrorSource::NODE_SPECIFIC, QMetaObject().className(), "element JSON_DERIVED not found", jsonNodeObject);
        if(deserializationSettings.needToReturn(errorLog))return;
    }
    QJsonObject derivedJson;
    if(derivedIt->isObject())
    {
        derivedJson = derivedIt->toObject();
    }
    else
    {
        errorLog.LogFatal(ErrorSource::NODE_SPECIFIC, QMetaObject().className(), "element JSON_DERIVED is not a object", jsonNodeObject);
        if(deserializationSettings.needToReturn(errorLog))return;
    }

    //deserialize base
    QJsonObject::iterator base = jsonNodeObject.find(JSON_BASE);
    if(base == jsonNodeObject.end()){
        errorLog.LogFatal(ErrorSource::NODES_BASE, QMetaObject().className(), "element JSON_BASE not found", jsonNodeObject);
        if(deserializationSettings.needToReturn(errorLog))return;
    }
    QJsonObject baseJson;
    if(base->isObject()){
        baseJson = base->toObject();
    }
    else{
        errorLog.LogFatal(ErrorSource::NODES_BASE, QMetaObject().className(), "element JSON_BASE is not a object", baseJson);
        if(deserializationSettings.needToReturn(errorLog))return;
    }

    //deserialize settings
    QJsonObject::iterator settings = jsonNodeObject.find(JSON_NODE_SETTINGS);
    if(settings == jsonNodeObject.end()){
        errorLog.LogError(ErrorSource::NODES_SETTINGS, QMetaObject().className(), "element JSON_NODE_SETTINGS not found", jsonNodeObject);
        if(deserializationSettings.needToReturn(errorLog))return;
    }
    QJsonObject settingsJson;
    if(settings->isObject()){
        settingsJson = settings->toObject();
    }
    else{
        errorLog.LogError(ErrorSource::NODES_SETTINGS, QMetaObject().className(), "element JSON_SETTINGS is not a object", settingsJson);
        if(deserializationSettings.needToReturn(errorLog))return;
    }

    VisualNodeBase* newNode = nullptr;
    newNode = constructNode(baseJson, derivedJson, settingsJson, deserializationSettings, errorLog);
    if(deserializationSettings.needToReturn(errorLog))return;

    if(newNode)
    {
        scene->addItem(newNode);
    }
    else
    {
        errorLog.LogFatal(ErrorSource::NODES_BASE, metaObject()->className(), "newNode is nullptr", jsonNodeObject);
        if(deserializationSettings.needToReturn(errorLog))return;
    }
}
VisualNodeBase* LoadStore::constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog)
{
    VisualNodeBase* newNode = nullptr;
    if(derivedJson.contains(JSON_NODE_TYPE))
    {
        QString type = derivedJson.find(JSON_NODE_TYPE)->toString();
        if(VisualFilteredConsole::classNameEquals(type))
        {
            newNode = new VisualFilteredConsole(baseJson, derivedJson, settingsJson, deserializationSettings, errorLog);
        }
    }
    else
    {
        errorLog.LogFatal(ErrorSource::NODE_SPECIFIC, metaObject()->className(), "element JSON_NODE_TYPE not found", derivedJson);
        if(deserializationSettings.needToReturn(errorLog))return nullptr;
    }
    return newNode;
}
