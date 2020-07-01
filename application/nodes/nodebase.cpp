#include "nodebase.h"


NodeBase::NodeBase(DbgLogger *dbgLogger)
    :dbgLogger(dbgLogger)
{

}

NodeBase::~NodeBase()
{

}

void NodeBase::leftHistoricalUpdateOccured()
{
    dbgLogger->debug("NodeBase", __FUNCTION__,"called");
}


