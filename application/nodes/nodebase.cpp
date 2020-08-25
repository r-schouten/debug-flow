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

//std::string NodeBase::getNodeName()
//{
//    return "NodeBase";
//}


