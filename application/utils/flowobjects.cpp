#include "flowobjects.h"


DbgLogger *FlowObjects::getDbgLogger() const
{
    return dbgLogger;
}

WindowManager *FlowObjects::getWindowManager() const
{
    return windowManager;
}

HistoricalUpdateManager *FlowObjects::getHistoricalUpdateManager() const
{
    return historicalUpdateManager;
}

UpdateManager *FlowObjects::getUpdateManager() const
{
    return updateManager;
}



FlowObjects::FlowObjects(SelectionManager *_selectionManager, UndoRedoManager *_undoredoManager, DbgLogger *_dbgLogger, WindowManager *_windowManager, HistoricalUpdateManager *_historicalUpdateManager, UpdateManager *_updateManager)
{
    dbgLogger = _dbgLogger;
    if(_selectionManager == nullptr)
    {
        qFatal("[fatal][FlowContext] _selectionManager == nullptr");
    }
    if(_undoredoManager == nullptr)
    {
        qFatal("[fatal][FlowContext] _undoredoManager == nullptr");
    }
    windowManager = _windowManager;
    selectionManager = _selectionManager;
    undoRedoManager = _undoredoManager;
    historicalUpdateManager = _historicalUpdateManager;
    updateManager = _updateManager;
}

FlowObjects::~FlowObjects()
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
VisualConnection* FlowObjects::findConnection(uint64_t uniqueId)
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
    dbgLogger->warning("FlowData",__FUNCTION__,"connection with id %lld not found", uniqueId);
    QListIterator<VisualConnection*> it2(connections);
    while(it2.hasNext())
    {
        VisualConnection* current = it2.next();
        printf("- %lld", current->getUniqueId());
    }
    return nullptr;
}

VisualNodeBase *FlowObjects::findnode(int64_t uniqueId)
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
    dbgLogger->warning("FlowData",__FUNCTION__,"connection with id %lld not found", uniqueId);
    QListIterator<VisualNodeBase*> it2(nodes);
    while(it2.hasNext())
    {
        VisualNodeBase* current = it2.next();
        printf("- %lld  %s", current->getUniqueId(), current->name.toStdString().c_str());
    }
    return nullptr;
}
SelectionManager *FlowObjects::getSelectionManager()
{
    return selectionManager;
}

UndoRedoManager *FlowObjects::getUndoRedoManager()
{
    return undoRedoManager;
}

