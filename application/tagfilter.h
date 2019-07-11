//Rene Schouten
//July 2019
//this class provide filter functions for tags
//tags are information hidden in the text
//also ansi escape codes can be filtered
#pragma once
#include <QTextCharFormat>
#include <qdebug.h>
#include "circularbufferreader.h"

//https://en.wikipedia.org/wiki/ANSI_escape_code
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
struct ANSICodes
{
    QList<ANSICode> code;
    bool found = false;
};

class TagFilter
{
public:
    TagFilter();
    bool filterData(QString *destination, CircularBufferReader *bufferReader, QTextCharFormat* format);
private:
    void processTag(int begin, int end);

    //fuction should be able to both write to a qstring and a circular buffer, to place the data a lambda function must be given
    bool filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader, QTextCharFormat* format);
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
};
