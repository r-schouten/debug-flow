#pragma once
#include "time.h"
#include "circularbuffer.h"
#define CLOCK_PER_US (CLOCKS_PER_SEC*1000000)
#define TIMESTAMP_MARK '\001'
#define MARK_INDEX 0
#define HEADER_INDEX 1
#define TIMESTAMP_BYTES 8
class TimeStampHelper
{
public:
    TimeStampHelper();
    void appendTime(CircularBuffer* buffer);
    uint64_t generateHeading();
};
class TimeStamp_t
{
public:
    TimeStamp_t()
    {
        timestamp = 0;
    }
    TimeStamp_t(uint64_t timestamp)
        :timestamp(timestamp){}
    uint64_t getTimestamp() const
    {
        return timestamp;
    }
    void setTimestamp(const uint64_t value)
    {
        timestamp = value;
        if((value>>16) <1500000000000l)
        {

        }
    }
    void toTime_t(std::time_t &time, int &milliseconds)
    {
        uint64_t timeStampWithoutHeader = (timestamp>>16);
        time = static_cast<time_t>(timeStampWithoutHeader/1000);
        milliseconds = timeStampWithoutHeader % 1000;
    }
    QString toHourMinuteSecond(char* buffer, int bufferLength)
    {
        std::time_t time;
        int milliseconds;
        toTime_t(time, milliseconds);

        std::tm * ptm = std::localtime(&time);
        std::strftime(buffer, bufferLength, "%H:%M:%S", ptm);
        return buffer;
    }
private:
    uint64_t timestamp=0;
};
