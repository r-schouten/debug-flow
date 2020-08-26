#include "mergehelper.h"

MergeHelper::MergeHelper()
{

}

void MergeHelper::analyze(CircularBufferReader *reader, MergeState_t *mergeState)
{
    if(mergeState->ready == MergeReady_t::READY)
    {
        return;
    }

    int sourceAvailable = reader->availableSize();
    int i = 0;
    for(;i<sourceAvailable;i++)
    {
        const char &character = (*reader)[i];
        if((character == METADATA_MARK))
        {
            if(i + TIMESTAMP_BYTES >= sourceAvailable)
            {
                break;
            }
            i += 2;//skip the header
            uint64_t timestamp64 = 0;
            uint8_t* timestamp8 = (uint8_t*)&timestamp64;
            int end = i + TIMESTAMP_BYTES - 2;
            for(;i < end;i++)
            {
                const char &character = (*reader)[i];
                *timestamp8 = (uint8_t)character;
                timestamp8++;
            }
            i--;
            mergeState->lastTimestamp.setTimeStamp(timestamp64);
            if(mergeState->ready == MergeReady_t::NOT_READY)
            {
                mergeState->ready = MergeReady_t::TIMESTAMP_FOUND;
            }
            else
            {

            }
        }
        if(character == '\n')
        {
            if(mergeState->ready == MergeReady_t::TIMESTAMP_FOUND)
            {
                mergeState->ready = MergeReady_t::READY;
                mergeState->availableSize = i+1;
                return;
            }
        }
    }
}
bool MergeHelper::readMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i)
{
    i += 2;//skip the header
    uint64_t timestamp64 = 0;
    uint8_t* timestamp8 = (uint8_t*)&timestamp64;
    int end = i+TIMESTAMP_BYTES - 2;
    for(;i < end;i++)
    {
        const char &character = (*bufferReader)[i];
        *timestamp8 = (uint8_t)character;
        timestamp8++;
    }
    i--;
    currentMetaData->setTimeStamp(timestamp64);
    return true;
}
