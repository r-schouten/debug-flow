#pragma once
#include "dbglogger.h"
#include "circularbuffer.h"
#include "nodebase.h"
#include "inputnode.h"
#include "outputnode.h"
#include "updatemanager.h"
#include "metadatahelper.h"
#include "contextfilterengine.h"

#include "mergehelper.h"

class InputNode;
class OutputNode;
class Subscription
{
private:
    InputNode* inputNode;
    OutputNode* outputNode;
    UpdateManager* updateManager;
    DbgLogger* dbgLogger;

    UpdateNr_t updateNr=0;
public:
    Subscription(InputNode *_inputNode, OutputNode *_outputNode, CircularBufferReader *reader, UpdateManager* updageManager, DbgLogger *dbgLogger);
    ~Subscription();

    OutputNode *getOutputNode();
    InputNode *getInputNode() const;

    UpdateNr_t getUpdateNr() const;

    UpdateReturn_t notifyBufferUpdate();


    CircularBufferReader* bufferReader;
    //for merging
    MergeState_t mergeState;
};

