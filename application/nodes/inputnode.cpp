#include "inputnode.h"

InputNode::InputNode()
{
    hasInput = true;
    mergeHelper = new MergeHelper;
}

InputNode::~InputNode()
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {

        iterator.next()->remove();
    }
}

void InputNode::notifyUnsubscribe(Subscription *subscription)
{
    subScriptions.removeOne(subscription);
}

void InputNode::addSubscription(OutputNode *outputNode)
{
    subScriptions.append(outputNode->subscribe(this));
}

void InputNode::deleteSubscription(OutputNode *outputNode)
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {

        Subscription* subscription = iterator.next();
        if(subscription->getOutputNode() == outputNode)
        {
            subscription->remove();
        }
    }
}
std::string InputNode::getNodeName()
{
    return "InputNode";
}

QList<Subscription *>* InputNode::getSubScriptions()
{
    return &subScriptions;
}

//------historical update feature--------
void InputNode::resetBufferReader(Subscription *caller)
{
    caller->bufferReader->reset();
}

void InputNode::bufferReaderToBegin(Subscription *caller)
{
    dbgLogger->debug("InputNode",__FUNCTION__,"called");
    caller->bufferReader->toBegin();
}

UpdateReturn_t InputNode::notifyBufferUpdate(Subscription *source)
{
    if(subScriptions.count() <= 1)
    {
        return doBufferUpdate(source, source->bufferReader->availableSize());
    }
    else
    {
        return doMergeUpdate(source);
    }

}

UpdateReturn_t InputNode::doMergeUpdate(Subscription *source)
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        mergeHelper->analyze(subscription->bufferReader, &subscription->mergeState);//todo, not all of them need this
    }
    while(true)
    {
        //dbgLogger->debug("InputNode",__FUNCTION__,"start");
        if(allSubsReady() == false)break;
        Subscription* oldestUpdate = findOldest();
        if(oldestUpdate == nullptr)break;
        if(oldestUpdate->mergeState.ready != READY)break;


        UpdateReturn_t returnState = doBufferUpdate(oldestUpdate, oldestUpdate->mergeState.availableSize);
        if(returnState == ROUTE_DELAYED)return ROUTE_DELAYED;

        oldestUpdate->mergeState.ready = NOT_READY;
        mergeHelper->analyze(oldestUpdate->bufferReader, &oldestUpdate->mergeState);
    }

    if(source->getOutputNode()->isProcessingDone())
    {
        return UpdateReturn_t::UPDATE_DONE;
    }
    else
    {
        return UpdateReturn_t::ROUTE_DELAYED;
    }
}

bool InputNode::allSubsReady()
{
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        if(subscription->mergeState.ready == MergeReady_t::NOT_READY)
        {
            return false;
        }
    }
    return true;
}
Subscription* InputNode::findOldest()//can return nullptr
{
    uint64_t oldestTimeStamp = UINT64_MAX;
    Subscription* oldestSubscription = nullptr;
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        if(subscription->mergeState.ready != MergeReady_t::NOT_READY)
        {
            uint64_t currentTimeStamp = subscription->mergeState.lastTimestamp.getTimeStamp();
            //dbgLogger->printf("%llu \n",currentTimeStamp);
            if(currentTimeStamp <= oldestTimeStamp)
            {
                oldestTimeStamp = currentTimeStamp;
                oldestSubscription = subscription;
            }
            else if(currentTimeStamp == oldestTimeStamp)
            {
                if(oldestSubscription->mergeState.ready == TIMESTAMP_FOUND)
                {
                    oldestTimeStamp = currentTimeStamp;
                    oldestSubscription = subscription;
                }
            }

        }
    }
    return oldestSubscription;
}


bool InputNode::areAllOtherSubscriptionsUpdated(UpdateNr_t updateNr, Subscription* currentSubscription)
{
    if(subScriptions.length() <= 1)return true;
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        if(subscription != currentSubscription)
        {
            if(subscription->getUpdateNr() != updateNr)
            {
                return false;
            }
        }
    }
    return true;
}

void InputNode::notifyHistoricalUpdateFinished()
{
    //do nothing, this function can be optionally overrided
}

void InputNode::lock()
{
    locked = true;
}

void InputNode::unlock()
{
    locked = false;
}

bool InputNode::isLocked()
{
    return locked;
}

