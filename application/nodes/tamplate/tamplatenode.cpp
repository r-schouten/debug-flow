#include "tamplatenode.h"


TamplateNode::TamplateNode(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :NodeBase(updateManager,dbgLogger)
{
#ifdef INPUTNODE
    nodeInput = new NodeInput(updateManager, dbgLogger, static_cast<NodeBase*>(this));
    nodeInput->setDoBufferUpdateCallback(std::bind(&TamplateNode::doBufferUpdate,this,std::placeholders::_1,std::placeholders::_2));
#endif
#ifdef OUTPUTNODE
    circularBuffer = new CircularBuffer(dbgLogger,"tamplate", TAMPLATE_BUFFER_SIZE, TAMPLATE_BUFFER_SIZE, true);
    nodeOutput = new NodeOutput(updateManager, circularBuffer, dbgLogger, this);
#endif
    settings = new TamplateNodeSettings(dbgLogger);
#ifdef OUTPUTNODE
    circularBuffer = new CircularBuffer(dbgLogger,"tamplate", TAMPLATE_BUFFER_SIZE, TAMPLATE_BUFFER_SIZE, true);
    metaDataHelper = new MetaDataHelper;
#endif
#ifdef INPUTNODE
    //connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));
#endif
}

TamplateNode::~TamplateNode()
{
#ifdef OUTPUTNODE
   delete nodeOutput;
#endif
#ifdef INPUTNODE
    delete NodeInput;
#endif
    delete settings;
}


//implement for debug purposes
std::string TamplateNode::getNodeName()
{
    return "TamplateName";
}

TamplateNodeSettings* TamplateNode::getNodeSettings()
{
    return settings;
}

void TamplateNode::reset()
{

}

int TamplateNode::amountOfInputs()
{
#ifdef INPUTNODE
    return 1;
#endif
    return 0;
}
int TamplateNode::amountOfOutputs()
{
#ifdef OUTPUTNODE
    return 1;
#endif
    return 0;
}

NodeInput *TamplateNode::getInput(int index)
{
#ifdef INPUTNODE
    return nodeInput;
#endif
    return nullptr;
}

NodeOutput *TamplateNode::getOutput(int index)
{
#ifdef OUTPUTNODE
    return nodeOutput;
#endif
    return nullptr;
}
#ifdef INPUTNODE
void TamplateNode::NotifyBufferUpdate(Subscription *source)
{
    //do somethings with the data
#ifdef OUTPUTNODE
    notifyAllSubscriptions();
#endif
}

void TamplateNode::notifyHistoricalUpdateFinished()
{

}
#endif
#ifdef OUTPUTNODE
//send some data into the system, doesn't matter from what kind of function it comes from
void TamplateNode::dataReceived()
{
    updateManager->initateUpdate(nodeOutput);
}
#endif
