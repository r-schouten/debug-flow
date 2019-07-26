#include "contextfilter.h"

ContextFilter::ContextFilter()
{

}
bool ContextFilter::filterData(QString* destination, CircularBufferReader *bufferReader, QTextCharFormat *format)
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
    ANSICodes ansiCodes;
    return filterData(lambda, cargeReturnLambda, bufferReader, format);
}

bool ContextFilter::filterData(const std::function<void(char)>& addChar, const std::function<bool()>& deleteCarageReturnLambda, CircularBufferReader *bufferReader, QTextCharFormat *format)
{
    int contextBeginIndex = 0;
    int ANSIBeginIndex = 0;
    int releaseLength = 0;

    bool readingInContext = false;
    bool readingANSIEscape = false;
    bool styleChanged = false;
    int availableSize = bufferReader->availableSize();
    for(int i=0;i<availableSize;i++)
    {
        const char character = (*bufferReader)[i];
        qDebug() << character;
        if(readingInContext)
        {
            if(character == ']')
            {
                processContext(bufferReader,contextBeginIndex,i);
                if((keepContext)&&(showCurrentContext))
                {
                    for(int j=contextBeginIndex;j<=i;j++)
                    {
                        addChar((*bufferReader)[j]);
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
                styleChanged = true;
                break;
            }
        }
        else {
            if(character == '[')
            {
                readingInContext = true;
                contextBeginIndex = i;
            }

            else if(character == '\033')
            {
                readingANSIEscape = true;
                ANSIBeginIndex = i;
            }
            else {
                if(showCurrentContext)
                {
                    addChar(character);
                }
                releaseLength++;
            }
        }
    }
    //never split a \r\n, it will result in a 'random' newline
    if(releaseLength > 0)
    {
        if(deleteCarageReturnLambda())
        {
            releaseLength--;
        }
    }
    bufferReader->release(releaseLength);
    return styleChanged;
}
void ContextFilter::processContext(CircularBufferReader *bufferReader, int begin, int end)
{
    showCurrentContext = true;
    int beginOfProperty = begin+1;
    int propertyIndex = 0;
    QString property;
    property.reserve(end - begin);
    for(int i = begin+1;i<end;i++)
    {
        const char character = (*bufferReader)[i];

        if((character == ',')||(character == ' '))
        {
            processproperty(property,propertyIndex);
            beginOfProperty = i + 1;
            propertyIndex++;
            property.clear();
        }
        else {
            property.append(character);
        }
    }
    processproperty(property,propertyIndex);
}
void ContextFilter::processproperty(QString& properyName, int propertyIndex)
{
    if(context.size() <= propertyIndex)
    {
        context.append(new Property);
    }
    Property* property = context.at(propertyIndex);
    PropertyOption* option = property->getOption(properyName);
    if(option == nullptr)
    {
        property->options.append(new PropertyOption(properyName,true));
        emit propertyChanged(property);
    }
    else {
        if(option->getEnabled() == false)
        {
            showCurrentContext = false;
        }
    }
}

//only supports SGR parameters
//https://en.wikipedia.org/wiki/ANSI_escape_code
bool ContextFilter::processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat* format,int beginIndex, int endIndex)
{
    //there is no code with less than 3 chars
    if(endIndex - beginIndex + 1 < 3)return false;

    //-----first char-----
    int index = beginIndex;
    if((*bufferReader)[index] != '\033')//first character is/should the esc code
    {
        qDebug("error TagFilter::processANSIEscape() :(*bufferReader)[index] != '\033' %c",(*bufferReader)[index]);
        return true;
    }
    index++;
    if(index >= endIndex)return false;

    //-----second char-----
    if((*bufferReader)[index] != '[')//first character is/should be [, others are not supported yet
    {
        qDebug("error TagFilter::processANSIEscape() :(*bufferReader)[index] != '[' %c",(*bufferReader)[index]);
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
        qDebug("[Error][tagFilter] ansi escape code to long");
        return true;
    }
    return false;
}
void ContextFilter::applyANSICode(QTextCharFormat* format, ANSICode ansiCode)
{
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
