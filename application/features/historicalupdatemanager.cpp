#include "historicalupdatemanager.h"

HistoricalUpdateManager::HistoricalUpdateManager(DbgLogger* dbgLogger)
    :dbgLogger(dbgLogger)
{

}

void HistoricalUpdateManager::initatiateHistoricalUpdate(NodeBase *node)
{
    dbgLogger->debug("HistoricalUpdateManager",__FUNCTION__,"called");

    historicalEventCounter++;
    historicalUpdate(node,true, 0);

    for (auto const& i : sourcesList) {
        i->doHistoricalUpdate();
        i->notifyAllSubscriptions();
    }
    sourcesList.clear();
}
//recursive function
void HistoricalUpdateManager::historicalUpdate(NodeBase *node, bool forwardReset,int depth)
{
    //to prevent circular endles recursion, only run when it is the first update for this event.
    if(node->HistoricalUpdateEventNr != historicalEventCounter)
    {
        node->HistoricalUpdateEventNr = historicalEventCounter;
        node->eventState = INITIATING;
    }
    else
    {
        return;
    }
    node->eventState = INITIATED;

    InputNode* inputNode = nullptr;
    OutputNode* outputNode = nullptr;
    if(node->hasInput) inputNode = dynamic_cast<InputNode*>(node);
    if(node->hasOutput) outputNode = dynamic_cast<OutputNode*>(node);

    //reset this node
    if(forwardReset)
    {
        node->reset();
    }

    if(node->hasOutput)
    {
        if(outputNode->bufferHistoricalCapable())
        {
            sourcesList.push_front(outputNode);
        }
        else
        {
            if(forwardReset)
            {
                outputNode->resetBuffer();
            }
            dbgLogger->printf("children on output %d:\n",depth);
            QListIterator<Subscription*> i(*outputNode->getSubscribers());
            while (i.hasNext())
            {
                Subscription* toChildNode = i.next();
                InputNode* childNode = toChildNode->getInputNode();
                dbgLogger->printf("- %s\n",childNode->getNodeName().c_str());

                if(childNode->HistoricalUpdateEventNr != historicalEventCounter)
                {
                    if(forwardReset == false)
                    {
                        childNode->lock();
                    }
                    else
                    {
                        historicalUpdate(childNode, forwardReset, depth+1);
                    }
                }
            }
        }
    }
    if(node->hasInput)
    {
        dbgLogger->printf("parents on input %d:\n",depth);

        QListIterator<Subscription*> i(*inputNode->getSubScriptions());
        while (i.hasNext())
        {
            Subscription* toParentNode = i.next();
            OutputNode* parentNode = toParentNode->getOutputNode();
            dbgLogger->printf("- %s\n",parentNode->getNodeName().c_str());

            historicalUpdate(parentNode, false, depth-1);
        }
    }
}
