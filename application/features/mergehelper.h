#pragma once
#include "circularbufferreader.h"
#include "metadatahelper.h"


enum MergeReady_t
{
    NOT_READY,
    TIMESTAMP_FOUND,
    READY
};

struct MergeState_t
{
    MetaData_t lastTimestamp;
    int updateNr = 0;
    MergeReady_t ready = NOT_READY;
    int availableSize;
};

class MergeHelper
{
public:
    MergeHelper();
    void analyze(CircularBufferReader *reader, MergeState_t* mergeState);
private:
    bool readMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i);
};

