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
