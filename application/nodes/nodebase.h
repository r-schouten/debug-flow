#pragma once
#include "nodesettingsbase.h"

class UpdateManager;
class NodeSettingsBase;
class NodeInput;
class NodeOutput;
class NodeBase
{
public:
    NodeBase(UpdateManager* updateManager, DbgLogger* dbgLogger);
    virtual ~NodeBase();

    //function implemented by all derived classes to acces the node settings
    virtual NodeSettingsBase* getNodeSettings()=0;
    virtual std::string getNodeName() = 0;
    virtual void reset();

    virtual int amountOfInputs() = 0;
    virtual int amountOfOutputs() = 0;
    bool hasInput();
    bool hasOutput();

    virtual NodeInput* getInput(int index) = 0;
    virtual NodeOutput* getOutput(int index) = 0;

    int HistoricalUpdateEventNr = -1;
protected:
    UpdateManager* updateManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
};

