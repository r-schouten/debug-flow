#include "updatemanager.h"
#include "outputnode.h"
UpdateManager::UpdateManager(DbgLogger *dbgLogger)
    :dbgLogger(dbgLogger)
{

}

uint64_t UpdateManager::initateUpdate(OutputNode* sourceNode)
{
    updateNr++;
    depth = 0;
    dbgLogger->verbose("UpdateManager",__FUNCTION__,"%d",updateNr);

    while(sourceNode->notifyAllSubscriptions() != UpdateReturn_t::UPDATE_DONE);

    return updateNr;
}

uint64_t UpdateManager::getUpdateNr()
{
    return updateNr;
}
