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
        jsonObject.insert("derived", *derivedJson);
        jsonObject.insert("base", *baseJson);
        jsonObject.insert("settings", *nodeSettingsJson);
        jsonObject.insert("connections", "nullptr");

//        QJsonObject nodeJsonObject;
//        nodeJsonObject.insert("node",jsonObject);

        allObjectsJson.append(jsonObject);

        delete derivedJson;
        delete baseJson;
        delete nodeSettingsJson;
    }
    QJsonObject *completeNodeJson = new QJsonObject;
    completeNodeJson->insert("nodes",allObjectsJson);
    return completeNodeJson;
}

void LoadStore::deserialize(QJsonObject &jsonObject)
{
    QJsonArray nodesJson = jsonObject.find("nodes").value().toArray();
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
    QJsonObject::iterator derivedIt = jsonNodeObject.find("derived");
    if(derivedIt != jsonNodeObject.end())
    {
        QJsonObject derivedJson = derivedIt.value().toObject();
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
    QJsonObject::iterator base = jsonNodeObject.find("base");
    if(base != jsonNodeObject.end())
    {
        QJsonObject baseJson = base.value().toObject();
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
    QJsonObject::iterator settings = jsonNodeObject.find("base");
    if(settings != jsonNodeObject.end())
    {
        QJsonObject settingsJson = settings.value().toObject();
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

    QString type = jsonNodeObject.find("type").value().toString();
    if(type == VisualFilteredConsole::staticMetaObject.className())
    {
        qDebug("deserializing derived");
        newNode = new VisualFilteredConsole();
        newNode->deserialize(jsonNodeObject);
    }
    return newNode;
}
void LoadStore::deserializeSettings(QJsonObject &jsonNodeObject)
{

}


