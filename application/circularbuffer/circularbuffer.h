#pragma once
#include <QObject>
#include <iostream>
#include <QMutexLocker>

#include "circularbufferreader.h"
#include "dbglogger.h"

class CircularBufferReader;
class NodeInfoViewer;

enum ResizeOperationState_t
{
    NO_OPERATION,
    STARTED,
    WRITING_IN_NEW_BUFFER
};

class CircularBuffer
{
private:
    DbgLogger* dbgLogger = nullptr;
    std::string name;
    char* writeBuffer;//the pointer to the begin of the buffer
    char* originalBuffer = nullptr;
    char* resizeBuffer = nullptr;

    int head;
    int conditionalHead;
    int iterations = 0;
    int capacity;
    int newBufferCapacity;
    int oldBufferCapacity;
    int maxCapacity;
    bool historicalCapable;

    int minTail = 0;
    int minTailIteration = 0;

    ResizeOperationState_t resizeOperation = NO_OPERATION;

    QMutex writeMutex;
    void checkSize(int neededSize);
    void returnToBegin();
public:
    CircularBuffer(DbgLogger *dbgLogger, std::string name, const int _capacity = 1000, const  int _maxCapacity = 100000, bool historicalCapable = false);
    ~CircularBuffer();
    //todo copy and move constructor

    void append(char *inputData, int size);//prefered
    void append(const QByteArray *data);
    void appendByte(char *inputData);

    void startConditional();
    void conditionalAppend(char *inputData);
    void commit();


    void resetTail();
    void calcTail(CircularBufferReader *reader);
    int unUsedSize();

    void print();
    void reset();
    CircularBufferReader *requestNewReader();

    bool isHistoricalCapable() const;

    friend CircularBufferReader;
    friend NodeInfoViewer;
    void resize(int newCapacity);
};


