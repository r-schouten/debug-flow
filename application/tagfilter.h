#pragma once
#include <qdebug.h>
#include "circularbufferreader.h"

enum class ANSIType
{
    NONE,
    UNKNOWN,
    FORMATTING,
    EREASE,
    CURSOR,
    SCREENMODE,
    ERROR
};

struct ANSICode
{
    ANSIType type = ANSIType::NONE;
    int value = 0;
};


class TagFilter
{
public:
    TagFilter();
    ANSICode filterData(QString *destination, CircularBufferReader *bufferReader);
private:
    void processTag(int begin, int end);
    void filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader, ANSICode* potentialANSICode);
    void processANSIEscape(CircularBufferReader *bufferReader, ANSICode *potentialANSICode, int beginIndex, int endIndex);
};
