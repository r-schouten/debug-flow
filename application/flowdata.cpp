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
    return nullptr;
}
