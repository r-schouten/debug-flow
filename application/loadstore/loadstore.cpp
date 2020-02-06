#include "loadstore.h"

LoadStore::LoadStore(FlowData* flowData, NodeScene* scene)
    :flowData(flowData),scene(scene)
{

}
QJsonObject *LoadStore::serialize()
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

        QJsonObject* derivedJson = node->serialize();
        QJsonObject* baseJson = node->serializeBase();
        if(node->getNode()->getNodeSettings() == nullptr)
        {
            qFatal("[fatal][NodeScene] node->getNode()->getNodeSettings() == nullptr");
        }
        QJsonObject* nodeSettingsJson = node->getNode()->getNodeSettings()->serialize();

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



void LoadStore::deserialize(QJsonObject &jsonObject)
{
    QJsonArray nodesJson = jsonObject.find(JSON_NODES)->toArray();
    QJsonArray::iterator it;
    for (it = nodesJson.begin(); it != nodesJson.end(); it++) {
        QJsonObject object = it->toObject();
        deserializeNode(object);
    }
}
void LoadStore::deserializeNode(QJsonObject &jsonNodeObject)
{
    //deserialize derived
    QJsonObject::iterator derivedIt = jsonNodeObject.find(JSON_DERIVED);
    if(derivedIt == jsonNodeObject.end())
    {
        qFatal("[fatal][LoadStore] can't find derived tag");
    }

    //deserialize base
    QJsonObject::iterator base = jsonNodeObject.find(JSON_BASE);
    if(base == jsonNodeObject.end())
    {
        qFatal("[fatal][LoadStore] can't find base tag");
    }

    //deserialize settings
    QJsonObject::iterator settings = jsonNodeObject.find(JSON_NODE_SETTINGS);
    if(settings == jsonNodeObject.end())
    {
        qFatal("[fatal][LoadStore] can't find settings tag");
    }

    QJsonObject baseJson = base->toObject();
    QJsonObject derivedJson = derivedIt->toObject();
    QJsonObject settingsJson = settings->toObject();

    VisualNodeBase* newNode = nullptr;
    newNode = constructNode(baseJson, derivedJson, settingsJson);

    if(newNode)
    {
        scene->addItem(newNode);
    }
    else
    {
        qFatal("[fatal][LoadStore] newNode is nullptr");
    }


}
VisualNodeBase* LoadStore::constructNode(QJsonObject &baseJson, QJsonObject &derivedJson, QJsonObject &settingsJson)
{
    VisualNodeBase* newNode = nullptr;

    QString type = derivedJson.find(JSON_NODE_TYPE)->toString();
    if(type == VisualFilteredConsole::staticMetaObject.className())
    {
        newNode = new VisualFilteredConsole(baseJson, derivedJson, settingsJson);
    }
    return newNode;
}


