#pragma once
#include "nodesettingsbase.h"

class NodeSettingsBase;
class NodeBase
{
public:
    NodeBase(DbgLogger* dbgLogger);
    virtual ~NodeBase();
    bool hasInput = false;
    bool hasOutput = false;

    //function implemented by all derived classes to acces the node settings
    virtual NodeSettingsBase* getNodeSettings()=0;

protected:
    DbgLogger* dbgLogger = nullptr;
};

