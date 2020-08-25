#pragma once
#include "dbglogger.h"
#include "circularbuffer.h"
#include "nodebase.h"
#include "inputnode.h"
#include "outputnode.h"
#include "updatemanager.h"
#include "metadatahelper.h"
#include "contextfilterengine.h"

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

    UpdateReturn_t notifyBufferUpdate();
    CircularBufferReader* bufferReader;

    void remove();
    UpdateNr_t getUpdateNr() const;

    MetaData_t lastMetaData;
    uint64_t mergeUpdateNr = 0;
    filterReturnValue_t filterValue = filterReturnValue_t::ALL_DATA_PROCESSED;
};

