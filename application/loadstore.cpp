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
    VisualNodeBase* newNode = nullptr;
    //deserialize derived
    QJsonObject::iterator derivedIt = jsonNodeObject.find(JSON_DERIVED);
    if(derivedIt != jsonNodeObject.end())
    {
        QJsonObject derivedJson = derivedIt->toObject();
        newNode = deserializeDerived(derivedJson);
    }
    else
    {
        qFatal("[fatal][LoadStore] can't find derived tag");
    }
    if(newNode == nullptr)
    {
        qFatal("[fatal][LoadStore] newNode == nullptr");
    }

    //deserialize base
    QJsonObject::iterator base = jsonNodeObject.find(JSON_BASE);
    if(base != jsonNodeObject.end())
    {
        QJsonObject baseJson = base->toObject();
        newNode->deserializeBase(baseJson);
    }
    else
    {
        qFatal("[fatal][LoadStore] can't find base tag");
    }

    if(newNode)
    {
        scene->addItem(newNode);
    }
    else
    {
        qFatal("[fatal][LoadStore] newNode is nullptr");
    }

    //deserialize settings
    //note scene->addItem need to run before loading the settings
    QJsonObject::iterator settings = jsonNodeObject.find(JSON_NODE_SETTINGS);
    if(settings != jsonNodeObject.end())
    {
        QJsonObject settingsJson = settings->toObject();
        if(newNode->getNode())
        {
            newNode->getNode()->getNodeSettings()->deserialize(settingsJson);
        }
        else
        {
             qFatal("[fatal][LoadStore] getNode is nullptr");
        }
    }
    else
    {
        qFatal("[fatal][LoadStore] can't find settings tag");
    }

}
VisualNodeBase* LoadStore::deserializeDerived(QJsonObject &jsonNodeObject)
{
    QJsonDocument doc(jsonNodeObject);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    qDebug(strJson.toStdString().c_str());

    VisualNodeBase* newNode = nullptr;

    QString type = jsonNodeObject.find(JSON_NODE_TYPE)->toString();
    if(type == VisualFilteredConsole::staticMetaObject.className())
    {
        qDebug("deserializing derived");
        newNode = new VisualFilteredConsole();
        newNode->deserialize(jsonNodeObject);
    }
    return newNode;
}


