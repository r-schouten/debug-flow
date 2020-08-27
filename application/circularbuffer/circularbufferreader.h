#pragma once
#include <QObject>
#include <circularbuffer.h>

class CircularBuffer;
class CircularBufferReader
{
private:
    CircularBuffer* buffer = nullptr;
    int tail = 0;
    int iteration = 0;
    char* readBuffer = nullptr;
    CircularBufferReader(CircularBuffer* buffer, int tail, int iteration);
    int usedSize();
    int unUsedSize();
public:
    ~CircularBufferReader();
    int availableSize();
    char &operator [](int i);
    char &at(int i);

    void release(int index);
    void reset();
    void toBegin();

    friend CircularBuffer;
    int getIteration() const;
    int getTail() const;

    int capacity = 0;//a copy of the original buffer capacity

};
