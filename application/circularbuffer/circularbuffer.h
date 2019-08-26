#pragma once
#include <QObject>
#include <iostream>
#include <circularbufferreader.h>
class CircularBufferReader;
class CircularBuffer
{
private:
    char* data;
    int head;
    int iterations = 0;
    int capacity;
    int maxCapacity;
    void checkSize(int neededSize);
public:
    CircularBuffer();
    CircularBuffer(const int _capacity, const  int _maxCapacity);
    ~CircularBuffer();
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


