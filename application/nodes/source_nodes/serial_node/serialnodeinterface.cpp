#include "serialnodeinterface.h"

SerialNodeInterface::SerialNodeInterface(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{

}

SerialNodeInterface::~SerialNodeInterface()
{
    delete settings;
}

std::string SerialNodeInterface::getNodeName()
{
    return "SerialNodeInterface";
}

SerialSettings *SerialNodeInterface::getNodeSettings()
{
    return settings;
}
