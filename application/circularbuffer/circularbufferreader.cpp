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
//    if(length == 0)
//    {
//        qDebug("error CircularBufferReader::release(int length) : length == 0");
//    }
    if(length < 0)
    {
        qFatal("error CircularBufferReader::release(int length) : length < 0");
    }
    if(availableSize() < length)
    {
        qFatal("error CircularBufferReader::release(int length) : availableSize() < length");
    }
#endif
    tail += length;
    if(tail >= buffer->capacity)
    {
        tail -= buffer->capacity;
        iteration++;
    }

}
