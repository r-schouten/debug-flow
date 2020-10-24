#pragma once
#include "dbglogger.h"
#include "nodeInput.h"
#include "nodeoutput.h"
#include "updatemanager.h"

class HistoricalUpdateManager
{
public:
    HistoricalUpdateManager(UpdateManager* updateManager, DbgLogger* dbgLogger);
    void initatiateHistoricalUpdate(NodeBase* node);

protected:
    void historicalUpdate(NodeBase *node, bool forwardReset, int depth);
    UpdateManager* updateManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
    int historicalEventCounter = 0;

    std::list<NodeOutput*> sourcesList;
    std::list<NodeInput*> lockedNodes;
    std::list<NodeInput*> inputNodes;

};

