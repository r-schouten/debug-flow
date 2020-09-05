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

    profileCounter = 0;
    timer.start();
    measurementPoint(ZERO_MEASUREMENT_START);
    measurementPoint(ZERO_MEASUREMENT_END);


    while(sourceNode->notifyAllSubscriptions() != UpdateReturn_t::UPDATE_DONE);

    measurementPoint(FINISH);

    printMeasurement();

    return updateNr;
}

void UpdateManager::measurementPoint(ProfileSource_t source)
{
#ifdef PROFILE_ENABLED
    if(profileCounter >= MAX_AMOUNT_OF_MEAUSEMENTS)
    {
        //dbgLogger->fatal("updateManager",__FUNCTION__,"");
    }
    else
    {
        measurementList[profileCounter].source = source;
        measurementList[profileCounter].elapsed = timer.nsecsElapsed();
        profileCounter++;
    }
#endif
}
void UpdateManager::printMeasurement()
{
#ifdef PROFILE_ENABLED
    dbgLogger->debug("updateManager", __FUNCTION__, "measurement result");
    for(int i=0;i < profileCounter; i++)
    {
        int deltaT = 0;
        if(i>0)
        {
            deltaT = measurementList[i].elapsed - measurementList[i-1].elapsed;
        }
        dbgLogger->printf("%d %d     %s:    %d\n", i,deltaT, profileSourceText.at((int)measurementList[i].source).toStdString().c_str(), measurementList[i].elapsed);
    }
#endif
}
uint64_t UpdateManager::getUpdateNr()
{
    return updateNr;
}
