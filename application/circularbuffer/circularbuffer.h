#pragma once
#include <QObject>
#include <iostream>
#include "circularbufferreader.h"

#include "dbglogger.h"
class CircularBufferReader;
class CircularBuffer
{
private:
    DbgLogger* dbgLogger = nullptr;
    char* data;
    int head;
    int iterations = 0;
    int capacity;
    int maxCapacity;
    bool historicalCapable;

    int minTail = 0;
    int minTailIteration = 0;
    void checkSize(int neededSize);
public:
    CircularBuffer(DbgLogger *dbgLogger, const int _capacity = 1000, const  int _maxCapacity = 1000, bool historicalCapable = false);
    ~CircularBuffer();
    //todo copy and move constructor
    int usedSize(CircularBufferReader *reader);
    int unUsedSize(CircularBufferReader *reader);

    void append(char *inputData, int size);//prefered
    void append(const QByteArray *data);
    void appendByte(char *inputData);

    int getSize();

    void resetTail();
    void calcTail(CircularBufferReader *reader);
    int unUsedSize();

    void print();
    void reset();
    CircularBufferReader *requestNewReader();

    bool isHistoricalCapable() const;

    friend CircularBufferReader;
};


