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
QStringList ReturnText = {"UPDATE DONE","NOT DONE","DELAYED"};
UpdateReturn_t Subscription::notifyBufferUpdate()
{
    updateNr = updateManager->getUpdateNr();

//    int previousIteration = bufferReader->getIteration();
//    int previousTail = bufferReader->getTail();

//    updateManager->depth++;
    UpdateReturn_t updateReturn = inputNode->notifyBufferUpdate(this);
    //updateManager->depth--;

//    int bytes = (bufferReader->getIteration()-previousIteration) * bufferReader->capacity  + (bufferReader->getTail() - previousTail);
//    for(int i = 0;i<updateManager->depth;i++)
//    {
//        dbgLogger->printf("   ");
//    }
//    dbgLogger->verbose("Subscription",__FUNCTION__,"%p updated %s -> %s   (%s)   %d",this,getOutputNode()->getNodeName().c_str(),getInputNode()->getNodeName().c_str(),ReturnText[(int)updateReturn].toStdString().c_str(), bytes);


    OutputNode* nextOutputNode = dynamic_cast<OutputNode*>(inputNode);
    if(nextOutputNode)
    {
        int counter = 0;
        while(updateReturn == UpdateReturn_t::NOT_DONE)
        {
            //save variables for the safety mechanism, when this doesn't change the node has a bug with the processingDone variable
            int previousIteration = bufferReader->getIteration();
            int previousTail = bufferReader->getTail();
            if(counter == 0){
                dbgLogger->debug("Subscription", __FUNCTION__,"calling notifyBufferUpdate() again %s -> %s",getOutputNode()->getNodeName().c_str(),getInputNode()->getNodeName().c_str());
            }
            counter++;
            updateReturn = inputNode->notifyBufferUpdate(this);
            if(updateReturn != UpdateReturn_t::NOT_DONE)break;
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
    return updateReturn;
}
