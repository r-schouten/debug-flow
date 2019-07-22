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
    bool resizeEnabled = false;
    CircularBufferReader(CircularBuffer* buffer, int tail, int iteration, bool resizeEnabled = false);
public:
    ~CircularBufferReader();
    int availableSize();
    char &operator [](int i);
    char &at(int i);

    void release(int index);

    friend CircularBuffer;
};
