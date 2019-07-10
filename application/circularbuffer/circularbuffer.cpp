#include "circularbuffer.h"

CircularBuffer::CircularBuffer()
{
    CircularBuffer(100, 1000);
}

CircularBuffer::CircularBuffer(const int _capacity, const  int _maxCapacity)
    :capacity(_capacity),maxCapacity(_maxCapacity)
{
    data = (char*) malloc(capacity * sizeof(char));
    head = 0;

#ifdef QT_DEBUG
    std::cout << "constructor " << capacity<<std::endl;
    memset(data, 'x',capacity * sizeof(char));
#endif

}

CircularBuffer::~CircularBuffer()
{
    free(data);
}
int CircularBuffer::reset()
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
            qDebug("error CircularBuffer::usedSize() : iteration != buffer->iterations %d,%d    %d,%d",reader->iteration,reader->tail,iterations,head);
        }
#endif
        return head - reader->tail;
    }
    else {
#ifdef QT_DEBUG
        if(reader->iteration + 1 != iterations)
        {
            qDebug("error CircularBuffer::usedSize() : iteration + 1 != iterations");
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
        qDebug("CircularBuffer::checkSize(): if(neededSize >= capacity) %d",neededSize);
    }
}
void CircularBuffer::append(const QByteArray *byteArray)
{
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
