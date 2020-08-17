#include "circularbuffer.h"


CircularBuffer::CircularBuffer(DbgLogger *dbgLogger, const int _capacity, const int _maxCapacity, bool historicalCapable)
    :dbgLogger(dbgLogger),capacity(_capacity),maxCapacity(_maxCapacity),historicalCapable(historicalCapable)
{
    originalBuffer = (char*) malloc(capacity * sizeof(char));
    writeBuffer = originalBuffer;
    head = 0;

#ifdef QT_DEBUG
    memset(originalBuffer, 'x',capacity * sizeof(char));
#endif
}

CircularBuffer::~CircularBuffer()
{
    //todo resize
    free(originalBuffer);

    if(resizeOperation != NO_OPERATION)
    {
        free(resizeBuffer);
    }
}

void CircularBuffer::reset()
{
    //todo resize
    head = 0;
    iterations = 0;

    minTail = 0;
    minTailIteration = 0;

    if(resizeOperation != NO_OPERATION)
    {
        free(originalBuffer);
        capacity = newBufferCapacity;
        originalBuffer = resizeBuffer;
        writeBuffer = resizeBuffer;
    }
    oldBufferCapacity = capacity;
    resizeOperation = NO_OPERATION;

}
void CircularBuffer::returnToBegin()
{
    if(resizeOperation != NO_OPERATION)
    {
        if(resizeOperation == WRITING_IN_NEW_BUFFER)
        {
            resizeOperation = NO_OPERATION;

            free(originalBuffer);
            originalBuffer = resizeBuffer;
            resizeBuffer = nullptr;
        }
        if(resizeOperation == STARTED)
        {
            //all new data will be placed in the new buffer
            writeBuffer = resizeBuffer;
            capacity = newBufferCapacity;
            resizeOperation = WRITING_IN_NEW_BUFFER;
        }
    }
}
void CircularBuffer::resize(int newCapacity)
{
    if(resizeOperation != NO_OPERATION)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__, "resize operation is already going on");
        return;
    }
    if(newCapacity > maxCapacity)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__, "requested is larger than allowed by this node");
    }
    dbgLogger->debug("CircularBuffer",__FUNCTION__, "resize to %d", newCapacity);


    resizeBuffer = (char*) malloc(newCapacity * sizeof(char));
    resizeOperation = STARTED;
    newBufferCapacity = newCapacity;
    oldBufferCapacity = capacity;
}

int CircularBuffer::unUsedSize()
{
    if(minTail == INT_MAX)return capacity;
    if(head >= minTail)
    {
#ifdef QT_DEBUG
        if((minTailIteration != iterations)&&(head != 0))
        {
            dbgLogger->error("CircularBuffer",__FUNCTION__ ,"iteration != tail iterations %d,%d    %d,%d",minTailIteration, minTail,iterations,head);
        }
#endif
        return capacity - (head - minTail);
    }
    else {
#ifdef QT_DEBUG
        if(minTailIteration + 1 != iterations)
        {
            dbgLogger->error("CircularBuffer",__FUNCTION__ ,"tail iteration + 1 != iterations");
        }
#endif
        return minTail - head;
    }
}
void CircularBuffer::checkSize(int neededSize)
{
    if(neededSize >= capacity)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__ ,"if(neededSize >= capacity) %d",neededSize);
    }
    if(neededSize > unUsedSize())
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__ ,"if(neededSize >= unUsedSize()) %d %d",unUsedSize(), neededSize);
    }
}
void CircularBuffer::append(const QByteArray *byteArray)
{
    //take the raw data out of the byte array
    const char* data = static_cast<const char*>(*byteArray);
    append(const_cast<char*>(data), byteArray->length());
}

void CircularBuffer::append(char *inputData, int size)
{
    checkSize(size);
    int noSplitAvailable = capacity - head;
    int firstLength = std::min(noSplitAvailable, size);
    memcpy(writeBuffer+head, inputData, firstLength*sizeof(char));
    head += firstLength;
    if(head == capacity)//at the begin of the buffer
    {
        returnToBegin();
        head = 0;
        iterations++;
        int secondLength = size - firstLength;
        secondLength = std::min(secondLength, capacity);
        memcpy(writeBuffer, inputData+firstLength, secondLength*sizeof(char));
        head += secondLength;
    }
}

void CircularBuffer::appendByte(char *inputData)
{
    *(writeBuffer + head) = *inputData;
    head++;
    if(head == capacity)//at the begin of the buffer
    {
        returnToBegin();
        head = 0;
        iterations++;
    }
}

CircularBufferReader* CircularBuffer::requestNewReader()
{
    return new CircularBufferReader(this, head, iterations);
}

void CircularBuffer::resetTail()
{
    minTail = INT_MAX;
    minTailIteration = INT_MAX;
}
void CircularBuffer::calcTail(CircularBufferReader* reader)
{
    if(reader->iteration < minTailIteration)
    {
       minTailIteration = reader->iteration;
       minTail = reader->tail;
    }
    else if(reader->iteration == minTailIteration)
    {
        if(reader->tail < minTail)
        {
            minTail = reader->tail;
        }
    }

}

bool CircularBuffer::isHistoricalCapable() const
{
    return historicalCapable;
}

void CircularBuffer::print()
{
    std::cout << capacity << " buffer: ";
    for(int i=0;i < capacity;i++)
    {
        if(i == head)
        {
            std::cout << "|";
        }
        if((writeBuffer[i] == '\n')||(writeBuffer[i] =='\r'))
        {
            std::cout << " ";

        }
        else {
            std::cout << writeBuffer[i];
        }
    }
    std::cout << std::endl;
}
