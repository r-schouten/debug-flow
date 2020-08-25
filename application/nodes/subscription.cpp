#include "subscription.h"
#include "inputnode.h"
#include "outputnode.h"

Subscription::Subscription(InputNode *_inputNode, OutputNode *_outputNode, CircularBufferReader *reader, UpdateManager *updageManager, DbgLogger* dbgLogger)
    :inputNode(_inputNode),outputNode(_outputNode),bufferReader(reader),updateManager(updageManager),dbgLogger(dbgLogger)
{

}

UpdateNr_t Subscription::getUpdateNr() const
{
    return updateNr;
}


Subscription::~Subscription()
{
    inputNode->notifyUnsubscribe(this);
    outputNode->notifyUnsubscribe(this);
    delete bufferReader;
}

InputNode *Subscription::getInputNode() const
{
    return inputNode;
}
OutputNode *Subscription::getOutputNode()
{
    return outputNode;
}

void Subscription::remove()//use a function instead of a deconstructor so the caller don't have to delete the object
{
    delete this;
}
UpdateReturn_t Subscription::notifyBufferUpdate()
{
    updateNr = updateManager->getUpdateNr();

    UpdateReturn_t updateState = inputNode->NotifyBufferUpdate(this);
    OutputNode* nextOutputNode = dynamic_cast<OutputNode*>(inputNode);

    //review this after merging support, especially processing done
    while(updateState == NOT_DONE)
    {
        //save variables for the safety mechanism, when this doesn't change the node doesn't return a DONE state
        int previousIteration = bufferReader->getIteration();
        int previousTail = bufferReader->getTail();

        dbgLogger->debug("Subscription", __FUNCTION__,"calling notifyBufferUpdate() again");
        updateState = inputNode->NotifyBufferUpdate(this);
        if(updateState != NOT_DONE)break;
        if((previousIteration == bufferReader->getIteration()) && (previousTail == bufferReader->getTail()))
        {
            dbgLogger->fatal("Subscription", __FUNCTION__, "safety mechanism triggered, node has a NOT_DONE state but doensn't do anything\ncaused by node:%s",getInputNode()->getNodeName().c_str());
            return updateState;
        }
    }
    return updateState;
}
