#include "tagfilter.h"

TagFilter::TagFilter()
{

}
bool keepTag = true;
bool readingInTag = false;
void TagFilter::filterData(QString* destination, CircularBufferReader *bufferReader)
{
    auto lambda = [&](char character) mutable {destination->append(character);};
    auto cargeReturnLambda = [&]() mutable {
        if(destination->length() > 0)
        {
            if(destination->at(destination->length()-1) == QChar('\r')){
                destination->chop(1);
                return true;
            }
        }
        return false;
    };

    filterData(lambda, cargeReturnLambda, bufferReader);
}
void TagFilter::filterData(const std::function<void(char)>& addChar,const std::function<bool()>& deleteCarageReturnLambda, CircularBufferReader *bufferReader)
{
    int tagBeginIndex = 0;
    int releaseLength = 0;
    readingInTag = false;

    int availableSize = bufferReader->availableSize();
    for(int i=0;i<availableSize;i++)
    {
        const char character = (*bufferReader)[i];
        //std::cout << character;
        if(readingInTag)
        {
            if((*bufferReader)[i] == ']')
            {
                processTag(tagBeginIndex,i);
                if(keepTag)
                {
                    for(int j=tagBeginIndex;j<=i;j++)
                    {
                        addChar((*bufferReader)[j]);
                    }
                }
                releaseLength += i - tagBeginIndex+1;
                readingInTag = false;
            }
        }
        else {
            if((*bufferReader)[i] == '[')
            {
                readingInTag = true;
                tagBeginIndex = i;
            }
            else {
                addChar((*bufferReader)[i]);
                releaseLength++;
            }
        }
    }
    //never split a \r\n, it will result in a 'random' newline
    if(releaseLength >0)
    {
        if(deleteCarageReturnLambda())
        {
            releaseLength--;
        }
    }
    bufferReader->release(releaseLength);
}
void TagFilter::processTag(int begin, int end)
{

}
