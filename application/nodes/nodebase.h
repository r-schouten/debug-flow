#pragma once
#include "nodesettingsbase.h"

class UpdateManager;
class NodeSettingsBase;
class NodeBase
{
public:
    NodeBase(UpdateManager* updateManager, DbgLogger* dbgLogger);
    virtual ~NodeBase();
    bool hasInput = false;
    bool hasOutput = false;

    //function implemented by all derived classes to acces the node settings
    virtual NodeSettingsBase* getNodeSettings()=0;
    virtual std::string getNodeName() = 0;
    virtual void reset();

    int HistoricalUpdateEventNr = -1;
protected:
    UpdateManager* updateManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
};

