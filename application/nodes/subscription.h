#pragma once
#include "dbglogger.h"
#include "circularbuffer.h"
#include "nodebase.h"
#include "nodeInput.h"
#include "nodeoutput.h"
#include "updatemanager.h"
#include "metadatahelper.h"
#include "contextfilterengine.h"

#include "mergehelper.h"

class NodeInput;
class NodeOutput;
class Subscription
{
private:
    NodeInput* input;
    NodeOutput* outputNode;
    UpdateManager* updateManager;
    DbgLogger* dbgLogger;

    UpdateNr_t updateNr=0;
public:
    Subscription(NodeInput *_inputNode, NodeOutput *_outputNode, CircularBufferReader *reader, UpdateManager* updageManager, DbgLogger *dbgLogger);
    ~Subscription();

    NodeOutput *getOutputNode();
    NodeInput *getInput() const;

    UpdateNr_t getUpdateNr() const;

    UpdateReturn_t notifyBufferUpdate();


    CircularBufferReader* bufferReader;
    //for merging
    MergeState_t mergeState;
};

