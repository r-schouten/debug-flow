#pragma once

#include "nodeoutput.h"
#include "serialsettings.h"

#define SERIAL_NODE_BUFFER_SIZE 100000

class SerialNodeInterface: public NodeBase
{
public:
    SerialNodeInterface(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~SerialNodeInterface();
    virtual std::string getNodeName();
    virtual SerialSettings *getNodeSettings();

    int amountOfInputs(){return 0;}
    int amountOfOutputs(){return 1;}
    NodeInput *getInput(int index){return nullptr;}
    NodeOutput *getOutput(int index){return nodeOutput;}

protected:
    SerialSettings* settings = nullptr;

    virtual void openSerialPort()=0;
    virtual void closeSerialPort()=0;
    virtual void writeData(const char* data, const size_t length)=0;

    NodeOutput* nodeOutput = nullptr;
    CircularBuffer* circularBuffer = nullptr;
};

