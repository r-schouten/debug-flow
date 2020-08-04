#pragma once

#include "outputnode.h"
#include "serialsettings.h"

#define SERIAL_NODE_BUFFER_SIZE 100000

class SerialNodeInterface: public OutputNode
{
public:
    SerialNodeInterface(DbgLogger *dbgLogger);
    virtual ~SerialNodeInterface();
    virtual std::string getNodeName();
    virtual SerialSettings *getNodeSettings();

protected:
    SerialSettings* settings = nullptr;

    virtual void openSerialPort()=0;
    virtual void closeSerialPort()=0;
    virtual void writeData(const char* data, const size_t length)=0;
};

