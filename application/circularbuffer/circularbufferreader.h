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
    char** ptrToWriteBuffer = nullptr;//fix undefined variable errors in inline functions
    CircularBufferReader(CircularBuffer* buffer, int tail, int iteration);
    int usedSize();
    int unUsedSize();
public:
    ~CircularBufferReader();
    int availableSize();
    inline char &operator[](int i);
    inline char &at(int i);

    void release(int index);
    void reset();
    void toBegin();

    friend CircularBuffer;
    int getIteration() const;
    int getTail() const;

    int capacity = 0;//a copy of the original buffer capacity

};
//thread: main thread, consumer
inline char &CircularBufferReader::operator[] (int i)
{
    return at(i);
}

//thread: main thread, consumer
inline char &CircularBufferReader::at(int i)
{
    if(i + tail < capacity)
    {
        return readBuffer[i+tail];
    }
    else
    {
        return (*ptrToWriteBuffer)[i + tail - capacity];
    }
}
