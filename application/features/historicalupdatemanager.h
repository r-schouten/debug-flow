#pragma once
#include "dbglogger.h"
#include "inputnode.h"
#include "outputnode.h"
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

    std::list<OutputNode*> sourcesList;
    std::list<InputNode*> lockedNodes;
    std::list<InputNode*> inputNodes;

};

