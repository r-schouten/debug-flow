#include "serialnodeinterface.h"

SerialNodeInterface::SerialNodeInterface()
{
    settings = new SerialSettings();
    circularBuffer = new CircularBuffer(SERIAL_NODE_BUFFER_SIZE, SERIAL_NODE_BUFFER_SIZE);
}

SerialNodeInterface::~SerialNodeInterface()
{
    delete settings;
}

SerialSettings *SerialNodeInterface::getNodeSettings()
{
    return settings;
}
