#include "tagfilter.h"

TagFilter::TagFilter()
{

}
bool keepTag = true;
bool readingInTag = false;
bool readingANSIEscape = false;
ANSICode TagFilter::filterData(QString* destination, CircularBufferReader *bufferReader)
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
    ANSICode ansiCode;
    filterData(lambda, cargeReturnLambda, bufferReader, &ansiCode);
    return ansiCode;//return a copy of the ansi code
}
void TagFilter::filterData(const std::function<void(char)>& addChar,const std::function<bool()>& deleteCarageReturnLambda, CircularBufferReader *bufferReader,ANSICode* potentialANSICode)
{
    int tagBeginIndex = 0;
    int ANSIBeginIndex = 0;
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
        else if(readingANSIEscape)
        {
            std::cout << (*bufferReader)[i];
            processANSIEscape(bufferReader, potentialANSICode, ANSIBeginIndex,i);
            if(potentialANSICode->type != ANSIType::NONE)
            {
                releaseLength += i - ANSIBeginIndex+1;
                readingANSIEscape = false;
                break;
            }
        }
        else {
            if((*bufferReader)[i] == '[')
            {
                readingInTag = true;
                tagBeginIndex = i;
            }
            else if((*bufferReader)[i] == '\033')
            {
                readingANSIEscape = true;
                ANSIBeginIndex = i;
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
void TagFilter::processANSIEscape(CircularBufferReader *bufferReader, ANSICode* potentialANSICode,int beginIndex, int endIndex)
{
    //-----first char-----
    int index = beginIndex;
    if((*bufferReader)[index] != '\033')//first character is/should the esc code
    {
        qDebug("error TagFilter::processANSIEscape() :(*bufferReader)[index] != '\033' %c",(*bufferReader)[index]);
        potentialANSICode->type = ANSIType::ERROR;
    }
    index++;
    if(index >= endIndex)return;

    //-----second char-----
    if((*bufferReader)[index] != '[')//first character is/should be [
    {
        qDebug("error TagFilter::processANSIEscape() :(*bufferReader)[index] != '[' %c",(*bufferReader)[index]);
        potentialANSICode->type = ANSIType::ERROR;
    }
    index++;
    if(index >= endIndex)return;

    //-----third char-----
    int number = 0;
    if(((*bufferReader)[index] >= 48) && ((*bufferReader)[index] <= 57))//if character is a number in the ascii table
    {
        number = (*bufferReader)[index] - 48;
    }
    index++;
    if(index >= endIndex)return;

    //-----forth char-----
    //perhaps there is a second diget
    if(((*bufferReader)[index] >= 48) && ((*bufferReader)[index] <= 57))//if character is a number in the ascii table
    {
        number = number*10 + (*bufferReader)[index] - 48;
    }
    if((*bufferReader)[index] == 'm')//m is the end of a formatting code
    {
        potentialANSICode->type = ANSIType::FORMATTING;
        potentialANSICode->value = number;
    }
    index++;
    if(index >= endIndex)return;

    if((*bufferReader)[index] == 'm')//m is the end of a formatting code
    {
        potentialANSICode->type = ANSIType::FORMATTING;
        potentialANSICode->value = number;
    }
}
