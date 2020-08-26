#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager *historicalUpdateManager)
    :NodeBase(updateManager,dbgLogger),historcalUpdateManager(historicalUpdateManager)
{
    circularBuffer = new CircularBuffer(dbgLogger, "ContextFilter");
    settings = new ContextFilterSettings(dbgLogger);
    connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings,dbgLogger);
}


ContextFilterNode::~ContextFilterNode()
{
    delete settings;
    settings = nullptr;
    delete contextFilterEngine;
}

std::string ContextFilterNode::getNodeName()
{
    return CLASSNAME;
}
ContextFilterSettings *ContextFilterNode::getNodeSettings()
{
    return settings;
}

//void ContextFilterNode::filterData(CircularBuffer* buffer, CircularBufferReader *bufferReader)
//{
//    int amountOfSubscriptions = subScriptions.count();
//    if((settings->getMergeMode() == MergeMode_t::NO_CONTROL)||(amountOfSubscriptions == 1))
//    {
//        auto lambda = [&](char character) mutable {buffer->appendByte(&character);};
//        contextFilterEngine->filterData(lambda, bufferReader, bufferReader->availableSize(), getBufferUnusedSize(),&processingDone, &metaData);
        //return contextFilterEngine->filterDataMerge(buffer, bufferReader, bufferReader->availableSize(), getBufferUnusedSize(),&metaData, DONT_BREAK_ON_METADATA, false);
//    }
//    else if(settings->getMergeMode() == MergeMode_t::ON_NEW_LINE)
//    {
//        //return contextFilterEngine->filterDataMerge(buffer, bufferReader, bufferReader->availableSize(), getBufferUnusedSize(),&metaData, DONT_BREAK_ON_METADATA, true);
//    }
//    else if(settings->getMergeMode() == MergeMode_t::ON_TIMESTAMP)
//    {
//        int updatesDone = 0;
//        bool processingDone[amountOfSubscriptions];
//        for(int i = 0;i<amountOfSubscriptions;i++)
//        {
//            processingDone[i] = false;
//        }

//        int index =0;
//        int counter = 0;
//        //dbgLogger->debug(CLASSNAME,__FUNCTION__,"start merge on timestamp");
//        while(updatesDone != amountOfSubscriptions)
//        {
//            if(counter < amountOfSubscriptions)
//            {
//                //find lastest updated
//                int lastest = -1;
//                for(int i = 0;i < amountOfSubscriptions;i++)
//                {
//                    int updateNr = subScriptions.at(i)->mergeUpdateNr;
//                    if(updateNr > lastest)
//                    {
//                        index = i;
//                        lastest = updateNr;
//                    }
//                }
//                subScriptions.at(index)->mergeUpdateNr = 0;
//            }
//            else
//            {
//                //find oldest
//                uint64_t oldestTimestamp = UINT64_MAX;
//                for(int i = 0;i < amountOfSubscriptions;i++)
//                {
//                    if(processingDone[i] == false)
//                    {
//                        uint64_t timestamp = subScriptions.at(i)->lastMetaData.getTimeStamp();
//                        if(timestamp < oldestTimestamp)
//                        {
//                            index = i;
//                            oldestTimestamp = timestamp;
//                        }
//                    }
//                }
//            }

//            Subscription* subscription = subScriptions.at(index);
//            CircularBufferReader* currentReader = subscription->bufferReader;
//            if(counter < amountOfSubscriptions)
//            {
//                subscription->filterValue = contextFilterEngine->filterDataMerge(buffer, currentReader, currentReader->availableSize(), getBufferUnusedSize(),&subscription->lastMetaData, BREAK_ON_METADATA, false);
//            }
//            else
//            {
//                subscription->filterValue = contextFilterEngine->filterDataMerge(buffer, currentReader, currentReader->availableSize(), getBufferUnusedSize(),&subscription->lastMetaData, BREAK_ON_METADATA_EXEPT_FIRST, false);
//            }
//            subscription->mergeUpdateNr = counter;
//            //dbgLogger->debug(CLASSNAME,__FUNCTION__,"%d %llu    %d", index, subscription->lastMetaData.getTimeStamp(), subscription->filterValue);
//            if(subscription->filterValue == RETURN_ON_METADATA)
//            {

//            }
//            else if(subscription->filterValue == BUFFER_FULL)
//            {
//                //updateManager->addDelayedSubscription(subscription);
//                return filterReturnValue_t::BUFFER_FULL;
//            }
//            else
//            {
//                processingDone[index] = true;
//                updatesDone++;
//                return filterReturnValue_t::ALL_DATA_PROCESSED;
//            }
//            counter++;
//        }
//        return filterReturnValue_t::ALL_DATA_PROCESSED;
//    }
//}

void ContextFilterNode::doBufferUpdate(Subscription *source, int availableSize)
{
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }

    auto lambda = [&](char character) mutable {circularBuffer->appendByte(&character);};
    contextFilterEngine->filterData(lambda, source->bufferReader, availableSize, getBufferUnusedSize(),&processingDone, &metaData);
    notifyAllSubscriptions();

    //    if(settings->getMergeMode() == MergeMode_t::ON_TIMESTAMP)
//    {
//        if(!areAllOtherSubscriptionsUpdated(source->getUpdateNr(), source))
//        {
//           dbgLogger->debug("ContextFilterNode",__FUNCTION__,"areAllOtherSubscriptionsUpdated false from %s",source->getOutputNode()->getNodeName().c_str());
//           //updateManager->addDelayedSubscription(source);
//           return ROUTE_DELAYED;
//        }
//    }

    //return contextFilterEngine->filterDataMerge(buffer, bufferReade
    //filterData(circularBuffer, source->bufferReader, availableSize);



//    if(updateState == ROUTE_DELAYED)
//    {
//        return ROUTE_DELAYED;
//    }
//    if(filterValue == filterReturnValue_t::BUFFER_FULL)
//    {
//        return NOT_DONE;

//    }
//    else
//    {
//        return UPDATE_DONE;
//    }
}


void ContextFilterNode::reset()
{

}
void ContextFilterNode::initiateHistoricalUpdate()
{
    historcalUpdateManager->initatiateHistoricalUpdate(this);
}
