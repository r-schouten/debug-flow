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
void Subscription::notifyBufferUpdate()
{
    updateNr = updateManager->getUpdateNr();

    inputNode->notifyBufferUpdate(this);
    OutputNode* nextOutputNode = dynamic_cast<OutputNode*>(inputNode);
    //review this after merging support, especially processing done
    if(nextOutputNode)
    {
        int counter = 0;
        while(nextOutputNode->isProcessingDone() == false)
        {
            //save variables for the safety mechanism, when this doesn't change the node has a bug with the processingDone variable
            int previousIteration = bufferReader->getIteration();
            int previousTail = bufferReader->getTail();
            if(counter == 0){
                dbgLogger->debug("Subscription", __FUNCTION__,"calling notifyBufferUpdate() again %s -> %s",getOutputNode()->getNodeName().c_str(),getInputNode()->getNodeName().c_str());
            }
            counter++;
            inputNode->notifyBufferUpdate(this);
            if(nextOutputNode->isProcessingDone())break;
            if((previousIteration == bufferReader->getIteration()) && (previousTail == bufferReader->getTail()))
            {
                dbgLogger->error("Subscription", __FUNCTION__, "safety mechanism triggered, node has a processing done not set but doensn't do anything\ncaused by node:%s -> %s",getOutputNode()->getNodeName().c_str(),getInputNode()->getNodeName().c_str());
                break;
            }
        }
        if(counter > 1)
        {
            dbgLogger->printf("%d times",counter);

        }
    }
}
