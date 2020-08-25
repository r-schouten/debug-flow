#pragma once
#include "dbglogger.h"
enum UpdateReturn_t
{
    UPDATE_DONE,
    NOT_DONE,
    ROUTE_DELAYED
};

typedef uint64_t UpdateNr_t;

class Subscription;
class InputNode;
class OutputNode;
class UpdateManager
{
public:
    UpdateManager(DbgLogger* dbgLogger);

    UpdateNr_t initateUpdate();
    UpdateNr_t getUpdateNr();
    void finishUpdate();
    void addDelayedSubscription(Subscription* subscription);
private:
    DbgLogger* dbgLogger = nullptr;
    UpdateNr_t updateNr = 0;
    std::list<Subscription*> delayedSubscription;

};

