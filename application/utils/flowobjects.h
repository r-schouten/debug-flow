#pragma once

#include "selectionmanager.h"
#include "undoredomanager.h"
#include "historicalupdatemanager.h"
#include "dbglogger.h"
#include "windowmanager.h"
#include "visualnodebase.h"
#include "visualconnection.h"

class UndoRedoManager;
class SelectionManager;
class FlowObjects
{
private:
    SelectionManager* selectionManager = nullptr;
    UndoRedoManager* undoRedoManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
    WindowManager* windowManager = nullptr;
    HistoricalUpdateManager* historicalUpdateManager = nullptr;
public:
    FlowObjects(SelectionManager* _selectionManager, UndoRedoManager* _undoredoManager, DbgLogger* _dbgLogger, WindowManager* _windowManager, HistoricalUpdateManager* _historicalUpdateManager);
    ~FlowObjects();

    SelectionManager* getSelectionManager();
    UndoRedoManager* getUndoRedoManager();
    DbgLogger *getDbgLogger() const;

    //list with all nodes
    QList<VisualNodeBase*> nodes;

    //hold all connections, they are not graphics items
    QList<VisualConnection*> connections;

    VisualConnection *findConnection(uint64_t uniqueId);
    VisualNodeBase *findnode(int64_t uniqueId);
    WindowManager *getWindowManager() const;
    HistoricalUpdateManager *getHistoricalUpdateManager() const;
};

