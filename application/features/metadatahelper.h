#pragma once
#include "time.h"
#include "circularbuffer.h"
#define CLOCK_PER_US (CLOCKS_PER_SEC*1000000)
#define METADATA_MARK '\001'
#define MARK_INDEX 0
#define HEADER_INDEX 1
#define TIMESTAMP_BYTES 10
class MetaDataHelper
{
public:
    MetaDataHelper();
    void appendTime(CircularBuffer* buffer);
    void appendTime(QByteArray &bytearray);
    uint64_t generateHeading();
    uint64_t lastMetaData = 0;
    uint64_t startClock = 0;

};
class MetaData_t
{
public:
    MetaData_t();
    MetaData_t(uint64_t metadata);

    uint64_t getTimeStamp();
    void setTimeStamp(const uint64_t &value);

    void toTime_t(std::time_t &time, int &milliseconds);
    QString toHourMinuteSecond(char* buffer, int bufferLength);

private:
    uint64_t timestamp=0;
    uint16_t header=0;
};
