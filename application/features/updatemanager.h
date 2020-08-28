#pragma once
#include "dbglogger.h"
enum UpdateReturn_t
{
    UPDATE_DONE,
    NOT_DONE,
    ROUTE_DELAYED
};

typedef uint64_t UpdateNr_t;

class OutputNode;
class UpdateManager
{
public:
    UpdateManager(DbgLogger* dbgLogger);

    UpdateNr_t initateUpdate(OutputNode* sourceNode);
    UpdateNr_t getUpdateNr();
    int depth = 0;
private:
    DbgLogger* dbgLogger = nullptr;
    UpdateNr_t updateNr = 0;
};

