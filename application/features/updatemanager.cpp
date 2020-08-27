#include "updatemanager.h"

UpdateManager::UpdateManager(DbgLogger *dbgLogger)
    :dbgLogger(dbgLogger)
{

}

uint64_t UpdateManager::initateUpdate()
{
    updateNr++;
    depth = 0;
    //dbgLogger->verbose("UpdateManager",__FUNCTION__,"%d",updateNr);
    return updateNr;
}

uint64_t UpdateManager::getUpdateNr()
{
    return updateNr;
}
void UpdateManager::finishUpdate()
{

}
