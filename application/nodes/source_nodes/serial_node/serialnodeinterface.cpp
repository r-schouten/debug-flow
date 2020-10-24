#include "serialnodeinterface.h"

SerialNodeInterface::SerialNodeInterface(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :NodeBase(updateManager, dbgLogger)
{
    circularBuffer = new CircularBuffer(dbgLogger,"Serial", SERIAL_NODE_BUFFER_SIZE, SERIAL_NODE_BUFFER_SIZE, true);
    nodeOutput = new NodeOutput(updateManager,circularBuffer, dbgLogger, this);
}

SerialNodeInterface::~SerialNodeInterface()
{
    delete nodeOutput;
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
