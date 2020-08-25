#include "metadatahelper.h"

MetaDataHelper::MetaDataHelper()
{

}

void MetaDataHelper::appendTime(CircularBuffer *buffer)
{
    uint64_t headerWithTime = generateHeading();
    char* charRepresentation = (char*)&headerWithTime;

    //calculate result, overwrite some of the milliseconds_since_epoch since the full 64 bits are not needed.
    char header = METADATA_MARK;
    buffer->appendByte(&header);
    header = 1;//standard header without extra options
    buffer->appendByte(&header);
    buffer->append(charRepresentation,sizeof(uint64_t));
}
// Get time stamp in milliseconds.
uint64_t MetaDataHelper::generateHeading()
{
    uint64_t time =
        std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::microseconds(1);

    if(lastMetaData >= time)
    {
        time += lastMetaData + 1;
    }
    lastMetaData = time;

    return time;
}

MetaData_t::MetaData_t()
{
    timestamp = 0;
    header = 0;
}

MetaData_t::MetaData_t(uint64_t timestamp)
    :timestamp(timestamp){}


uint64_t MetaData_t::getTimeStamp()
{
    return timestamp;
}
void MetaData_t::setTimeStamp(const uint64_t &value)
{
    timestamp = value;
}


void MetaData_t::toTime_t(std::time_t &time, int &milliseconds)
{
    time = static_cast<time_t>(timestamp/1000000);
    milliseconds = (timestamp/1000) % 1000;
}

QString MetaData_t::toHourMinuteSecond(char *buffer, int bufferLength)
{
    std::time_t time;
    int milliseconds;
    toTime_t(time, milliseconds);

    std::tm * ptm = std::localtime(&time);
    std::strftime(buffer, bufferLength, "%H:%M:%S", ptm);
    return buffer;
}

