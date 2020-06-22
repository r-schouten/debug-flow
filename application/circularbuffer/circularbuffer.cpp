#include "circularbuffer.h"

CircularBuffer::CircularBuffer(DbgLogger *dbgLogger)
{
    CircularBuffer(dbgLogger, 100, 1000);
}

CircularBuffer::CircularBuffer(DbgLogger *dbgLogger, const int _capacity, const int _maxCapacity)
    :dbgLogger(dbgLogger),capacity(_capacity),maxCapacity(_maxCapacity)
{
    data = (char*) malloc(capacity * sizeof(char));
    head = 0;

#ifdef QT_DEBUG
    memset(data, 'x',capacity * sizeof(char));
#endif

}

CircularBuffer::~CircularBuffer()
{
    free(data);
}
void CircularBuffer::reset()
{
    head = 0;
}
int CircularBuffer::usedSize(CircularBufferReader* reader)
{
    if(head >= reader->tail)
    {
#ifdef QT_DEBUG
        if(reader->iteration != iterations)
        {
            dbgLogger->error("CircularBuffer",__FUNCTION__ ,"iteration != buffer->iterations %d,%d    %d,%d",reader->iteration,reader->tail,iterations,head);
        }
#endif
        return head - reader->tail;
    }
    else {
#ifdef QT_DEBUG
        if(reader->iteration + 1 != iterations)
        {
            dbgLogger->error("CircularBuffer",__FUNCTION__ ,"iteration + 1 != iterations");
        }
#endif
        return (capacity - reader->tail) + head;
    }
}
int CircularBuffer::unUsedSize(CircularBufferReader* reader)
{
     return capacity - usedSize(reader);
}

void CircularBuffer::checkSize(int neededSize)
{
    if(neededSize >= capacity)
    {
        dbgLogger->error("CircularBuffer",__FUNCTION__ ,"if(neededSize >= capacity) %d",neededSize);
    }
}
void CircularBuffer::append(const QByteArray *byteArray)
{
    //take the raw data out of the byte array
    const char* data = static_cast<const char*>(*byteArray);
    append(const_cast<char*>(data), byteArray->length());

    /*
    checkSize(byteArray->size());
    int noSplitAvailable = capacity - head;
    int firstLength = std::min(noSplitAvailable, byteArray->size());
    for(int i=0;i<firstLength;i++)
    {
        data[head] = byteArray->at(i);
        head++;
    }
    if(head == capacity)//at the begin of the buffer
    {
        head = 0;
        iterations++;
        int secondLength = byteArray->size() - firstLength;
        secondLength = std::min(secondLength, capacity);
        for(int i=0;i<secondLength;i++)
        {
            data[head] = byteArray->at(firstLength+i);
            head++;
        }
    }
    */
}

void CircularBuffer::append(char *inputData, int size)
{
    checkSize(size);
    int noSplitAvailable = capacity - head;
    int firstLength = std::min(noSplitAvailable, size);
    memcpy(data+head, inputData, firstLength*sizeof(char));
    head += firstLength;
    if(head == capacity)//at the begin of the buffer
    {
        head = 0;
        iterations++;
        int secondLength = size - firstLength;
        secondLength = std::min(secondLength, capacity);
        memcpy(data, inputData+firstLength, secondLength*sizeof(char));
        head += secondLength;
    }
}
CircularBufferReader* CircularBuffer::requestNewReader()
{
    return new CircularBufferReader(this, head, iterations, true);
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
        if((data[i] == '\n')||(data[i] =='\r'))
        {
            std::cout << " ";

        }
        else {
            std::cout << data[i];
        }
    }
    std::cout << std::endl;
}
