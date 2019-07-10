#pragma once
#include <qdebug.h>
#include "circularbufferreader.h"

class TagFilter
{
public:
    TagFilter();
    void filterData(QString *destination, CircularBufferReader *bufferReader);
private:
    void processTag(int begin, int end);
    void filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader);
};
