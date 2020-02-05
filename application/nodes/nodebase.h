#pragma once
#include "nodesettingsbase.h"

class NodeSettingsBase;
class NodeBase
{
public:
    NodeBase();
    virtual ~NodeBase();
    virtual void activate(){};
    bool hasInput = false;
    bool hasOutput = false;

    //function implemented by all derived classes to acces the node settings
    virtual NodeSettingsBase* getNodeSettings()=0;
};

