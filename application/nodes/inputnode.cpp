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
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        MergeState_t emptyMergeState;
        subscription->mergeState = emptyMergeState;
    }
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
        //multiple nodes are connected to the input, so we need to merge
        return doMergeUpdate(source);
    }

}

UpdateReturn_t InputNode::doMergeUpdate(Subscription *source)
{
    bool hasAlreadyHadAnUpdate = (source->mergeState.updateNr == updateManager->getUpdateNr());

    //update the update number of this specific subscription. its used to check whether the subscription was already updated
    source->mergeState.updateNr = updateManager->getUpdateNr();

    //run the analysis fuction on each subscription, to check whether they have memory in their buffer which can used
    QListIterator<Subscription*> iterator(subScriptions);
    while(iterator.hasNext())
    {
        Subscription* subscription = iterator.next();
        mergeHelper->analyze(subscription->bufferReader, &subscription->mergeState);//todo, not all of them need this

        //in case a subscription don't receive updates, and blocks everything
        if((subscription->mergeState.updateNr != updateManager->getUpdateNr())&&(hasAlreadyHadAnUpdate))
        {
            subscription->mergeState.ready = DISABLED;
        }
    }


    //in this loop data is forwarded, sorted on time
    bool delayed = false;
    while(true)
    {
        if(allSubsReady() == false)break;//if not all subs have data ready, it can not be deterimined whether there is older data available
        Subscription* oldestUpdate = findOldest(); //find the node with the lowest timestamp
        if(oldestUpdate == nullptr)break;//todo can this be optimized out
        if(oldestUpdate->mergeState.ready != READY)break;//subscriptions with the mergestate TIMESTAMP_FOUND where fine for comparing the timestamp. but need a update in order to become READY

        //do the update with this piece of data
        //todo implement segmentation, which can be rarely occur
        UpdateReturn_t returnState = doBufferUpdate(oldestUpdate, oldestUpdate->mergeState.availableSize);
        if(returnState == ROUTE_DELAYED)
        {
            delayed = true;
            break;
        }
        //analyze again
        oldestUpdate->mergeState.ready = NOT_READY;
        mergeHelper->analyze(oldestUpdate->bufferReader, &oldestUpdate->mergeState);
    }

    if((source->getOutputNode()->isProcessingDone()) && (delayed == false))
    {
        source->mergeState.lastReturn = UPDATE_DONE;
        return UpdateReturn_t::UPDATE_DONE;
    }
    else
    {
        //prevent a loop in the update system
        //never return ROUTE_DELAYED when the other node has already update done
        int doneCounter = 0;
        QListIterator<Subscription*> iterator(subScriptions);
        while(iterator.hasNext())
        {
            Subscription* subscription = iterator.next();
            if(subscription!= source)
            {
                if((subscription->mergeState.lastReturn == UPDATE_DONE)&&(subscription->mergeState.updateNr == updateManager->getUpdateNr()))
                {
                    doneCounter++;
                }
            }
        }
        if(doneCounter >= subScriptions.count()-1)
        {
            source->mergeState.lastReturn = UPDATE_DONE;
            return UpdateReturn_t::UPDATE_DONE;
        }
        else
        {
            source->mergeState.lastReturn = ROUTE_DELAYED;
            return UpdateReturn_t::ROUTE_DELAYED;
        }
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
        if((subscription->mergeState.ready == MergeReady_t::TIMESTAMP_FOUND) || (subscription->mergeState.ready == MergeReady_t::READY))
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

