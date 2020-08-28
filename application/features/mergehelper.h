#pragma once
#include "circularbufferreader.h"
#include "metadatahelper.h"
#include "updatemanager.h"

enum MergeReady_t
{
    NOT_READY,
    DISABLED,
    TIMESTAMP_FOUND,
    READY
};

struct MergeState_t
{
    MetaData_t lastTimestamp;
    UpdateNr_t updateNr = 0;
    MergeReady_t ready = NOT_READY;
    int availableSize;
    UpdateReturn_t lastReturn;
};

class MergeHelper
{
public:
    MergeHelper();
    void analyze(CircularBufferReader *reader, MergeState_t* mergeState);
private:
    bool readMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i);
};

