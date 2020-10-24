#include "historicalupdatemanager.h"

HistoricalUpdateManager::HistoricalUpdateManager(UpdateManager *updateManager, DbgLogger *dbgLogger)
    :updateManager(updateManager), dbgLogger(dbgLogger)
{

}


void HistoricalUpdateManager::initatiateHistoricalUpdate(NodeBase *node)
{
    dbgLogger->debug("HistoricalUpdateManager",__FUNCTION__,"called");
    historicalEventCounter++;
    historicalUpdate(node,true, 0);

    for (auto const& i : sourcesList) {
        i->doHistoricalUpdate();
        updateManager->initateUpdate(i);
    }
    sourcesList.clear();

    for (auto const& i : lockedNodes) {
        i->unlock();
    }
    lockedNodes.clear();

    for (auto const& i : inputNodes) {
        i->notifyHistoricalUpdateFinished();
    }
    inputNodes.clear();
}
//recursive function
void HistoricalUpdateManager::historicalUpdate(NodeBase *node, bool forwardReset,int depth)
{
    NodeInput* inputNode = node->getInput(0);
    NodeOutput* outputNode = node->getOutput(0);

    if(node->hasInput())//this is needed for a flow with merges
    {
        if(inputNode->isLocked())
        {
            inputNode->unlock();
        }
    }
    //to prevent circular endles recursion, only run when it is the first update for this event.
    if(node->HistoricalUpdateEventNr != historicalEventCounter)
    {
        node->HistoricalUpdateEventNr = historicalEventCounter;
    }
    else
    {
        return;
    }

    if(node->hasInput())
    {
        inputNodes.push_front(inputNode);
    }

    //reset this node
    if(forwardReset)
    {
        node->reset();
    }

    if(node->hasOutput())
    {
        if(outputNode->bufferHistoricalCapable())
        {
            sourcesList.push_front(outputNode);  
        }
        else if(forwardReset)
        {
            outputNode->resetBuffer();
        }
        dbgLogger->printf("children on output %d:\n",depth);
        QVectorIterator<Subscription*> i(*outputNode->getSubscribers());
        while (i.hasNext())
        {
            Subscription* toChildNode = i.next();
            NodeInput* childInput = toChildNode->getInput();
            NodeBase* childNode = childInput->getParent();
            dbgLogger->printf("- %s\n",childNode->getNodeName().c_str());

            if(childNode->HistoricalUpdateEventNr != historicalEventCounter)
            {
                if((forwardReset == false)||(outputNode->bufferHistoricalCapable()))
                {
                    childInput->lock();
                    lockedNodes.push_front(childInput);
                }
                else
                {
                    historicalUpdate(childNode, forwardReset, depth+1);
                }
            }
        }
    }
    if(node->hasInput())
    {
        dbgLogger->printf("parents on input %d:\n",depth);

        QVectorIterator<Subscription*> i(*inputNode->getSubScriptions());
        while (i.hasNext())
        {
            Subscription* toParentNode = i.next();
            NodeBase* parentNode = toParentNode->getOutputNode()->getParent();
            dbgLogger->printf("- %s\n",parentNode->getNodeName().c_str());

            historicalUpdate(parentNode, false, depth-1);
        }
    }
}

