#include "circularbufferreader.h"

int CircularBufferReader::getIteration() const
{
    return iteration;
}

int CircularBufferReader::getTail() const
{
    return tail;
}

CircularBufferReader::CircularBufferReader(CircularBuffer *buffer, int tail, int iteration)
    :buffer(buffer),tail(tail),iteration(iteration)
{
    readBuffer = buffer->writeBuffer;
    capacity = buffer->capacity;
}
CircularBufferReader::~CircularBufferReader()
{

}

int CircularBufferReader::usedSize()
{
    if(iteration < buffer->iterations)
    {
        if(tail < buffer->head)
        {
            buffer->dbgLogger->error("CircularBufferReader",__FUNCTION__ ," reader->tail < head %d,%d    %d,%d",iteration,tail,buffer->iterations,buffer->head);
        }
        return (capacity - tail) + buffer->head;

    }
    else if (iteration == buffer->iterations)
    {
        if(tail > buffer->head)
        {
            buffer->dbgLogger->error("CircularBufferReader",__FUNCTION__ ," reader->tail > head %d,%d    %d,%d",iteration,tail,buffer->iterations,buffer->head);
        }
        return buffer->head - tail;
    }
    else
    {
        buffer->dbgLogger->error("CircularBufferReader",__FUNCTION__ ," reader->iteration > iterations %d,%d    %d,%d",iteration,tail,buffer->iterations,buffer->head);
    }
    return 0;
}
int CircularBufferReader::unUsedSize()
{
     return capacity - usedSize();
}

int CircularBufferReader::availableSize()
{
    return usedSize();
}
char &CircularBufferReader::operator [] (int i)
{
    return at(i);
}

char &CircularBufferReader::at(int i)
{
    if(i + tail < capacity)
    {
        return readBuffer[i+tail];
    }
    else
    {
        return buffer->writeBuffer[i + tail - capacity];
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
    if(tail >= capacity)
    {
        tail -= capacity;
        iteration++;
        readBuffer = buffer->writeBuffer;
        capacity = buffer->capacity;
    }

}

void CircularBufferReader::reset()
{
    tail = buffer->head;
    iteration = buffer->iterations;
    readBuffer = buffer->writeBuffer;
    capacity = buffer->capacity;
}

void CircularBufferReader::toBegin()
{    
    if(buffer->resizeOperation == WRITING_IN_NEW_BUFFER)
    {
        tail = 0;
        iteration = buffer->iterations-1;
        capacity =  buffer->oldBufferCapacity;
        readBuffer = buffer->originalBuffer;
    }
    else if(buffer->iterations != 0)
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
