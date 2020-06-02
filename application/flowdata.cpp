#include "flowdata.h"

FlowData::FlowData(WindowManager *_windowManager)
    :windowManager(_windowManager)
{

}

FlowData::~FlowData()
{
    QListIterator<VisualConnection*> it(connections);
    while(it.hasNext())
    {
        VisualConnection* current = it.next();
        delete current;
    }
    QListIterator<VisualNodeBase*> it2(nodes);
    while(it2.hasNext())
    {
        VisualNodeBase* node = it2.next();
        delete node;
    }
}

VisualConnection* FlowData::findConnection(uint64_t uniqueId)
{
    QListIterator<VisualConnection*> it(connections);
    while(it.hasNext())
    {
        VisualConnection* current = it.next();
        if(current->getUniqueId() == uniqueId)
        {
            return current;
        }
    }
    qDebug("[debug][VisualConnection] connection with id %lld not found", uniqueId);
    QListIterator<VisualConnection*> it2(connections);
    while(it2.hasNext())
    {
        VisualConnection* current = it2.next();
        qDebug("- %lld", current->getUniqueId());
    }
    return nullptr;
}

VisualNodeBase *FlowData::findnode(int64_t uniqueId)
{
    QListIterator<VisualNodeBase*> it(nodes);
    while(it.hasNext())
    {
        VisualNodeBase* current = it.next();
        if(current->getUniqueId() == uniqueId)
        {
            return current;
        }
    }
    qDebug("[debug][VisualConnection] connection with id %lld not found", uniqueId);
    QListIterator<VisualNodeBase*> it2(nodes);
    while(it2.hasNext())
    {
        VisualNodeBase* current = it2.next();
        qDebug("- %lld  %s", current->getUniqueId(), current->name.toStdString().c_str());
    }
    return nullptr;
}
