#include "serialnodeinterface.h"

SerialNodeInterface::SerialNodeInterface(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{
    settings = new SerialSettings(dbgLogger);
    circularBuffer = new CircularBuffer(dbgLogger, SERIAL_NODE_BUFFER_SIZE, SERIAL_NODE_BUFFER_SIZE, true);
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
