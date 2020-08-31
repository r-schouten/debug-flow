#include "circularbuffer.h"

//thread: main thread
CircularBuffer::CircularBuffer(DbgLogger *dbgLogger, std::string name, const int _capacity, const int _maxCapacity, bool historicalCapable)
    :dbgLogger(dbgLogger),name(name),capacity(_capacity),maxCapacity(_maxCapacity),historicalCapable(historicalCapable)
{
    originalBuffer = (char*) malloc(capacity * sizeof(char));
    writeBuffer = originalBuffer;
    head = 0;

#ifdef QT_DEBUG
    memset(originalBuffer, 'x',capacity * sizeof(char));
#endif
}

//thread: main thread
//all buffer reader objects must be deleted first! The parent class is responsible for this
CircularBuffer::~CircularBuffer()
{
    //QMutexLocker locker(&writeMutex);
    //todo resize
    free(originalBuffer);

    if(resizeOperation != NO_OPERATION)
    {
        free(resizeBuffer);
    }
}

//thread: main thread
void CircularBuffer::reset()
{
    //QMutexLocker locker(&writeMutex);
    //todo resize
    head = 0;
    iterations = 0;

    resetTail();

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
//thread: main thread, producer thread
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
//thread: main thread
void CircularBuffer::resize(int newCapacity)
{
    //QMutexLocker locker(&writeMutex);
    if(resizeOperation != NO_OPERATION)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__, "%s resize operation is already going on",name.c_str());
        return;
    }
    if(newCapacity > maxCapacity)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__, "%s requested is larger than allowed by this node",name.c_str());
    }
    dbgLogger->debug("CircularBuffer",__FUNCTION__, "resize to %d", newCapacity);


    resizeBuffer = (char*) malloc(newCapacity * sizeof(char));
    resizeOperation = STARTED;
    newBufferCapacity = newCapacity;
    oldBufferCapacity = capacity;
}

//this method checks the available size based on the tail tracking principle
//thread: main thread, producer thread
int CircularBuffer::unUsedSize()
{
    if(minTail == INT_MAX)return capacity;
    if(head >= minTail)
    {
#ifdef QT_DEBUG
        if((minTailIteration != iterations)&&(head != 0))
        {
            //dbgLogger->error("CircularBuffer",__FUNCTION__ ,"%s iteration != tail iterations %d,%d    %d,%d",name.c_str(),minTailIteration, minTail,iterations,head);
        }
#endif
        return capacity - (head - minTail);
    }
    else {
#ifdef QT_DEBUG
        if(minTailIteration + 1 != iterations)
        {
            //dbgLogger->error("CircularBuffer",__FUNCTION__ ,"%s tail iteration + 1 != iterations",name.c_str());
        }
#endif
        return minTail - head;
    }
}
//thread: main thread, producer thread
void CircularBuffer::checkSize(int neededSize)
{
    if(neededSize >= capacity)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__ ,"%s if(neededSize >= capacity) %d",name.c_str(),neededSize);
    }
    if(neededSize > unUsedSize())
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__ ,"%s if(neededSize >= unUsedSize()) %d %d",name.c_str(),unUsedSize(), neededSize);
    }
}

//thread: main thread, producer thread
void CircularBuffer::append(const QByteArray *byteArray)
{
    //take the raw data out of the byte array
    const char* data = static_cast<const char*>(*byteArray);
    append(const_cast<char*>(data), byteArray->length());
}

//thread: main thread, producer thread
void CircularBuffer::append(char *inputData, int size)
{
    char* dbghelp = writeBuffer+head;
    //QMutexLocker locker(&writeMutex);
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
//thread: main thread, producer thread

void CircularBuffer::startConditional()
{
    conditionalHead = head;
}
//thread: main thread, producer thread
void CircularBuffer::conditionalAppend(char *inputData)
{
    //QMutexLocker locker(&writeMutex);
    *(writeBuffer + conditionalHead) = *inputData;
    conditionalHead++;
    if(conditionalHead == capacity)//at the begin of the buffer
    {
        conditionalHead = 0;
    }
}
void CircularBuffer::commit()
{
    if(conditionalHead < head)//it has returned to the begin
    {
        returnToBegin();
        iterations++;
    }
    head = conditionalHead;
}
//thread: main thread
CircularBufferReader* CircularBuffer::requestNewReader()
{
    //QMutexLocker locker(&writeMutex);
    return new CircularBufferReader(this, head, iterations);
}

//thread: main thread
void CircularBuffer::resetTail()
{
    minTail = INT_MAX;
    minTailIteration = INT_MAX;
}

//thread: main thread
void CircularBuffer::calcTail(CircularBufferReader* reader)
{
    //QMutexLocker locker(&writeMutex);
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

//thread: main thread
bool CircularBuffer::isHistoricalCapable() const
{
    return historicalCapable;
}

//thread: main thread
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
