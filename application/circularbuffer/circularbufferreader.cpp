#include "circularbufferreader.h"

CircularBufferReader::CircularBufferReader(CircularBuffer *buffer, int tail, int iteration, bool resize)
    :buffer(buffer),tail(tail),iteration(iteration),resizeEnabled(resize)
{

}
CircularBufferReader::~CircularBufferReader()
{

}
int CircularBufferReader::availableSize()
{
    return buffer->usedSize(this);
}
char &CircularBufferReader::operator [] (int i)
{
    return at(i);
}

char &CircularBufferReader::at(int i)
{
    if(i + tail < buffer->capacity)
    {
        return buffer->data[i+tail];
    }
    else
    {
        return buffer->data[i + tail - buffer->capacity];
    }
}

void CircularBufferReader::release(int length)
{
#ifdef QT_DEBUG

    if(length < 0)
    {
        buffer->dbgLogger->fatal("CircularBufferReader",__FUNCTION__,"length < 0");
    }
    if(availableSize() < length)
    {
        buffer->dbgLogger->fatal("CircularBufferReader",__FUNCTION__,"availableSize() < length");
    }
#endif
    tail += length;
    if(tail >= buffer->capacity)
    {
        tail -= buffer->capacity;
        iteration++;
    }

}

void CircularBufferReader::reset()
{
    tail = buffer->head;
    iteration = buffer->iterations;
}

void CircularBufferReader::toBegin()
{
    if(buffer->iterations != 0)
    {
        tail = buffer->head;
        iteration = buffer->iterations-1;
    }
    else
    {
        tail = 0;
        iteration = 0;
    }

}
