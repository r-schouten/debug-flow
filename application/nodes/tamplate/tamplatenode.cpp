#include "tamplatenode.h"


TamplateNode::TamplateNode(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :NodeBase(updateManager,dbgLogger)
{
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
    updateManager->initateUpdate(this);
}
#endif
