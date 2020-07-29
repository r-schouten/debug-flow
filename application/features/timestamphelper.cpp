#include "timestamphelper.h"

TimeStampHelper::TimeStampHelper()
{

}

void TimeStampHelper::appendTime(CircularBuffer *buffer)
{
    uint64_t headerWithTime = generateHeading();
    char* charRepresentation = (char*)&headerWithTime;
    buffer->append(charRepresentation,sizeof(uint64_t));
}
// Get time stamp in milliseconds.
uint64_t TimeStampHelper::generateHeading()
{
    uint64_t headerWithTime =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::milliseconds(1);

    uint8_t* byteRepresentation = (uint8_t*)&headerWithTime;
    //calculate result, overwrite some of the milliseconds_since_epoch since the full 64 bits are not needed.
    byteRepresentation[MARK_INDEX] = TIMESTAMP_MARK;
    byteRepresentation[HEADER_INDEX] = 1; //standard header without extra options

    return headerWithTime;
}
