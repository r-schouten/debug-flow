#include "contextfilterengine.h"

ContextFilterEngine::ContextFilterEngine(TagAndOptionsSettings *settings, DbgLogger* dbgLogger)
    :settings(settings),dbgLogger(dbgLogger)
{
    timeStampHelper = new TimeStampHelper();
}

void ContextFilterEngine::filterData(const std::function<void(char)>& addChar, CircularBufferReader *bufferReader, int sourceAvailable,int destinationAvailabe, bool* allDataProcessed)
{
    int contextBeginIndex = 0;
    int ANSIBeginIndex = 0;
    int releaseLength = 0;
    int charsAdded = 0;

    bool readingInContext = false;
    bool readingInTimestamp = false;
    int timeStampIndex = 0;
    *allDataProcessed = true;

    for(int i=0;i<sourceAvailable;i++)
    {
        const char character = (*bufferReader)[i];

        if(character == TIMESTAMP_MARK)
        {
            //the lenght of the timestamp is known, check whether there is enough space left
            if(i+7<sourceAvailable)
            {
                if(charsAdded +8 >= destinationAvailabe)
                {
                    *allDataProcessed = false;
                    break;
                }
            }
            else
            {
                break;
            }
            readingInTimestamp = true;
            timeStampIndex = i;
        }
        if(readingInTimestamp)
        {
            if(timeStampIndex + 8 <= i)
            {
                readingInTimestamp = false;
            }
        }
        if(readingInContext)
        {
            if(character == ']')
            {
                processContext(bufferReader,contextBeginIndex,i);
                if((!settings->getHideContext())&&(showCurrentContext))
                {
                    if(charsAdded + (i - contextBeginIndex + 1) >= destinationAvailabe)//it doesn't fit anymore
                    {
                        *allDataProcessed = false;
                        break;
                    }
                    for(int j=contextBeginIndex;j<=i;j++)
                    {
                        addChar((*bufferReader)[j]);
                        charsAdded++;
                    }
                }
                readingInContext = false;
                releaseLength += i - contextBeginIndex + 1;
            }
        }
        else {
            if((character == '[')&&(i - ANSIBeginIndex != 1))//ansi codes also use [
            {
                readingInContext = true;
                contextBeginIndex = i;
            }
            else
            {
                if(character == '\033')
                {
                    ANSIBeginIndex = i;
                }
                if(showCurrentContext)
                {
                    addChar(character);
                    charsAdded++;
                }
                releaseLength++;
            }
        }
        if(charsAdded >= destinationAvailabe)//it doesn't fit anymore
        {
            *allDataProcessed = false;
            break;
        }
    }
    bufferReader->release(releaseLength);
}
bool ContextFilterEngine::filterDataWithStyle(const std::function<void(char)>& addCharLambda, const std::function<void()>& styleChangedLambda, CircularBufferReader *bufferReader, QTextCharFormat *format, TimeStamp_t* currentTimeStamp)
{
    int contextBeginIndex = 0;
    int ANSIBeginIndex = 0;
    int releaseLength = 0;

    bool readingInContext = false;
    bool readingANSIEscape = false;
    bool readingInTimestamp = false;

    int timeStampIndex = 0;
    uint64_t timestamp64 = 0;
    uint8_t* timestamp8 = (uint8_t*)&timestamp64;

    int availableSize = bufferReader->availableSize();

    for(int i=0;i<availableSize;i++)
    {
        const char &character = (*bufferReader)[i];

        if((character == TIMESTAMP_MARK)&&(readingInTimestamp==false))
        {
            //the lenght of the timestamp is known, check whether there is enough space left
            if(i + TIMESTAMP_BYTES >= availableSize)
            {
                break;
            }
            styleChangedLambda();
            readingInTimestamp = true;
            timeStampIndex = i;

            timestamp8 = (uint8_t*)&timestamp64;
        }
        if(readingInTimestamp)
        {
            *timestamp8 = (uint8_t)character;
            timestamp8++;
            releaseLength++;
            if(timeStampIndex + TIMESTAMP_BYTES - 1 <= i)
            {
                readingInTimestamp = false;
                currentTimeStamp->setTimestamp(timestamp64);
            }
        }
        else
        {
            if(readingInContext)
            {
                if(character == ']')
                {
                    processContext(bufferReader,contextBeginIndex,i);
                    if((!settings->getHideContext())&&(showCurrentContext))
                    {
                        for(int j=contextBeginIndex;j<=i;j++)
                        {
                            char contextCharacter = (*bufferReader)[j];
                            if(contextCharacter == TIMESTAMP_MARK)
                            {
                                j+= TIMESTAMP_BYTES-1;
                                releaseLength -= TIMESTAMP_BYTES;
                            }
                            else
                            {
                                addCharLambda(contextCharacter);
                            }
                        }
                    }
                    releaseLength += i - contextBeginIndex + 1;
                    readingInContext = false;
                }
            }
            else if(readingANSIEscape)
            {
                bool done = processANSIEscape(bufferReader, format, ANSIBeginIndex,i);
                if(done)
                {
                    releaseLength += i - ANSIBeginIndex + 1;
                    readingANSIEscape = false;

                    styleChangedLambda();
                }
            }
            else if(readingInTimestamp == false){
                if(character == '[')
                {
                    readingInContext = true;
                    contextBeginIndex = i;
                }
                else if((character == '\033') && (settings->getANSIEnabled()))
                {
                    readingANSIEscape = true;
                    ANSIBeginIndex = i;
                }
                else {
                    if(showCurrentContext)
                    {
                        addCharLambda(character);
                    }
                    releaseLength++;
                }
            }
        }
    }
    bufferReader->release(releaseLength);
}

void ContextFilterEngine::processContext(CircularBufferReader *bufferReader, int begin, int end)
{
    showCurrentContext = true;
    int propertyIndex = 0;
    QString property;
    property.reserve(end - begin);
    for(int i = begin+1;i<end;i++)
    {
        const char character = (*bufferReader)[i];

        if(character == TIMESTAMP_MARK)//skip 8 characters
        {
            i += TIMESTAMP_BYTES - 1;//warning, notice that i might overflow and no other operation can be done before checking if its needed to break the loop
        }
        else
        {
            if((character == ',')||(character == ' '))
            {
                processOption(property,propertyIndex);
                propertyIndex++;
                property.clear();
            }
            else {
                property.append(character);
            }
        }
    }
    processOption(property,propertyIndex);
}
void ContextFilterEngine::processOption(QString& optionName, int tagIndex)
{

    if(settings->tags.size() <= tagIndex)
    {
        settings->tags.append(new Tag(QString("tag %1").arg(tagIndex),tagIndex));
    }
    Tag* tag = settings->tags.at(tagIndex);
    TagOption* option = tag->getOption(optionName);
    if(option == nullptr)
    {
        settings->addOption(tag, new TagOption(optionName,true));
    }
    else {
        if(option->enabled == false)
        {
            showCurrentContext = false;
        }
    }
}

//only supports SGR parameters
//https://en.wikipedia.org/wiki/ANSI_escape_code
bool ContextFilterEngine::processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat* format,int beginIndex, int endIndex)
{
    //there is no code with less than 3 chars
    if(endIndex - beginIndex + 1 < 3)return false;

    //-----first char-----
    int index = beginIndex;
    if((*bufferReader)[index] != '\033')//first character is/should the esc code
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"(*bufferReader)[index] != '\033' %c",(*bufferReader)[index]);
        return true;
    }
    index++;
    if(index >= endIndex)return false;

    //-----second char-----
    if((*bufferReader)[index] != '[')//first character is/should be [, others are not supported yet
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"(*bufferReader)[index] != '[' %c",(*bufferReader)[index]);
        return true;
    }
    index++;
    if(index >= endIndex)return false;

    //----->third char-----
    int number = 0;
    for(int i = index;i <=endIndex;i++)
    {
        if(((*bufferReader)[i] >= 48) && ((*bufferReader)[i] <= 57))//if character is a number in the ascii table
        {
            number = number * 10 + (*bufferReader)[i] - 48;
        }
        else if((*bufferReader)[i] == 'm')//m is the end of a formatting code
        {
            applyANSICode(format, {ANSIType::FORMATTING, number});
            return true;
        }
        else if((*bufferReader)[i] == ';')//m is the end of a formatting code
        {
            applyANSICode(format, {ANSIType::FORMATTING, number});
            number = 0;
        }
        else {
            //error
            return true;
        }
    }
    if(endIndex - beginIndex > 20)// todo magic number
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"ansi escape code to long");
        return true;
    }
    return false;
}
void ContextFilterEngine::applyANSICode(QTextCharFormat* format, ANSICode ansiCode)
{
    if(!format)return;
    if(ansiCode.type == ANSIType::FORMATTING)
    {
        if(ansiCode.value == 0)//reset code
        {
            QTextCharFormat defaultFormat;
            *format = defaultFormat;
        }
        else if(ansiCode.value == 1)//bold text code
        {
            format->setFontWeight(QFont::Bold);
        }
        else if(ansiCode.value == 2)//faint text code
        {
            format->setFontWeight(QFont::Thin);
        }
        else if(ansiCode.value == 3)//italic text code
        {
            format->setFontItalic(true);
        }
        else if(ansiCode.value == 4)//underline text code
        {
            format->setFontUnderline(true);
        }
        else if(ansiCode.value == 22)//no bold text code
        {
            format->setFontWeight(QFont::Normal);
        }
        else if(ansiCode.value == 23)//no italic text code
        {
            format->setFontItalic(false);
        }
        else if(ansiCode.value == 22)//no underline text code
        {
            format->setFontUnderline(false);
        }
        else if((ansiCode.value >= 30) && (ansiCode.value <= 37))
        {
            QList<QColor> ansiColors;
            ansiColors << Qt::black << Qt::red << Qt::green << Qt::yellow << Qt::blue << Qt::magenta << Qt::cyan << Qt::white;

            format->setForeground(ansiColors[ansiCode.value-30]);
        }
        else if((ansiCode.value >= 40) && (ansiCode.value <= 47))
        {
            QList<QColor> ansiColors;
            ansiColors << Qt::black << Qt::red << Qt::green << Qt::yellow << Qt::blue << Qt::magenta << Qt::cyan << Qt::white;
            format->setBackground(ansiColors[ansiCode.value-40]);
        }

    }

}
