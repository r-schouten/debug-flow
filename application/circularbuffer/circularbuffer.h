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
    void checkSize(int neededSize);
public:
    CircularBuffer(DbgLogger *dbgLogger);
    CircularBuffer(DbgLogger *dbgLogger, const int _capacity, const  int _maxCapacity);
    ~CircularBuffer();
    //todo copy and move constructor
    int usedSize(CircularBufferReader *reader);
    int unUsedSize(CircularBufferReader *reader);

    void append(char *inputData, int size);
    void append(const QByteArray *data);
    int getSize();
    void print();
    void reset();
    CircularBufferReader *requestNewReader();

    friend CircularBufferReader;
};


