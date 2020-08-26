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
    ~Subscription();
public:
    Subscription(InputNode *_inputNode, OutputNode *_outputNode, CircularBufferReader *reader, UpdateManager* updageManager, DbgLogger *dbgLogger);
    OutputNode *getOutputNode();
    InputNode *getInputNode() const;

    void notifyBufferUpdate();
    CircularBufferReader* bufferReader;

    void remove();
    UpdateNr_t getUpdateNr() const;

    //for merging
    MergeState_t mergeState;
};

