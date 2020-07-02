#pragma once
#include "nodesettingsbase.h"
enum HistoricalEvent
{
    INITIATING,
    INITIATED,
    PAUSED,
    DONE
};
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
    virtual std::string getNodeName() = 0;
    virtual void reset();

    int HistoricalUpdateEventNr = -1;
    HistoricalEvent eventState;
protected:

    DbgLogger* dbgLogger = nullptr;
};

