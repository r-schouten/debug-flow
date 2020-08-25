#include "serialnodeinterface.h"

SerialNodeInterface::SerialNodeInterface()
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
