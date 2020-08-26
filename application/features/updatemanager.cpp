#include "updatemanager.h"
#include "subscription.h"
UpdateManager::UpdateManager(DbgLogger *dbgLogger)
    :dbgLogger(dbgLogger)
{

}

uint64_t UpdateManager::initateUpdate()
{
    updateNr++;
    //dbgLogger->verbose("UpdateManager",__FUNCTION__,"%d",updateNr);
    return updateNr;
}

uint64_t UpdateManager::getUpdateNr()
{
    return updateNr;
}
void UpdateManager::finishUpdate()
{
//    dbgLogger->verbose("UpdateManager",__FUNCTION__,"delayed subscriptions:");
//    for (auto const& i : delayedSubscription) {
//        dbgLogger->printf("- %s -> %s\n",i->getOutputNode()->getNodeName().c_str(),i->getInputNode()->getNodeName().c_str());
//    }

//    for (auto i = delayedSubscription.begin(); i != delayedSubscription.end();) {
//            (*i)->notifyBufferUpdate();
//            i = delayedSubscription.erase(i);
//    }

//    dbgLogger->verbose("UpdateManager",__FUNCTION__,"delayed subscriptions after:");
//    for (auto const& i : delayedSubscription) {
//        dbgLogger->printf("- %s -> %s",i->getOutputNode()->getNodeName().c_str(),i->getInputNode()->getNodeName().c_str());
//    }
}

void UpdateManager::addDelayedSubscription(Subscription *subscription)
{
    delayedSubscription.push_front(subscription);
}
