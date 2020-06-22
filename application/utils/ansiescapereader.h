#pragma once
#include <QTextCharFormat>
#include "circularbufferreader.h"
#include "ansi_types.h"

class AnsiEscapeReader
{
public:
    AnsiEscapeReader();
    bool filterData(QString *destination, CircularBufferReader *bufferReader, QTextCharFormat* format);

private:
    bool filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader, QTextCharFormat* format);
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
};

