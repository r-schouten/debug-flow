#include "nodebase.h"

NodeBase::NodeBase(UpdateManager* updateManager, DbgLogger* dbgLogger)
    :updateManager(updateManager), dbgLogger(dbgLogger)
{

}

NodeBase::~NodeBase()
{

}

void NodeBase::reset()
{
    dbgLogger->fatal("NodeBase",__FUNCTION__, "base class called");
}

bool NodeBase::hasInput()
{
    return (amountOfInputs() != 0);
}

bool NodeBase::hasOutput()
{
     return (amountOfOutputs() != 0);
}

