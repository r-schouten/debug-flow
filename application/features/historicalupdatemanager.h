#pragma once
#include "dbglogger.h"
#include "inputnode.h"
#include "outputnode.h"

class HistoricalUpdateManager
{
public:
    HistoricalUpdateManager(DbgLogger* dbgLogger);
    void initatiateHistoricalUpdate(NodeBase* node);

protected:
    void historicalUpdate(NodeBase *node, bool forwardReset, int depth);
    DbgLogger* dbgLogger = nullptr;
    int historicalEventCounter = 0;
};

