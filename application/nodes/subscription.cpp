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

//QStringList ReturnText = {"UPDATE DONE","NOT DONE","DELAYED"};
UpdateReturn_t Subscription::notifyBufferUpdate()
{
    updateNr = updateManager->getUpdateNr();
    updateManager->measurementPoint(SUBSCRIPTION);
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

    return updateReturn;
}
