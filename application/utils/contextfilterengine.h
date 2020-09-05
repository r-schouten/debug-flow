//Rene Schouten
//July 2019
//this class provide filter functions for tags
//tags are information hidden in the text
//also ansi escape codes can be filtered
#pragma once
#include <QStandardItemModel>
#include <QTextCharFormat>
#include <qsignalmapper.h>
#include "circularbufferreader.h"
#include "ansi_types.h"
#include "tagandoptionssettings.h"
#include "metadatahelper.h"

//enum filterReturnValue_t
//{
//    BUFFER_FULL,
//    ALL_DATA_PROCESSED,
//    LAST_NEWLINE,
//    RETURN_ON_METADATA,
//    RETURN_ON_ERROR,
//    RETURN_ON_STYLECHANGE
//};
enum MetaDataBreak_t
{
    DONT_BREAK_ON_METADATA,
    BREAK_ON_METADATA,
    BREAK_ON_METADATA_EXEPT_FIRST
};

class ContextFilterEngine: public QObject
{
    Q_OBJECT

public:
    ContextFilterEngine(TagAndOptionsSettings* settings, DbgLogger *dbgLogger);

    void filterData(const std::function<void (char)> &addChar, CircularBufferReader *bufferReader, int sourceAvailable, int destinationAvailabe, bool *allDataProcessed, MetaData_t *currentMetaData);
    //UpdateReturn_t filterDataMerge(CircularBuffer *buffer, CircularBufferReader *bufferReader, int sourceAvailable, int destinationAvailabe, MetaData_t *currentMetaData, MetaDataBreak_t metaDataBreak, bool stopOnNewLine);
    void filterDataWithStyle(const std::function<void(char)>& addCharLambda, const std::function<void()>& styleChangedLambda, CircularBufferReader *bufferReader, int availableSize, QTextCharFormat *format, MetaData_t* currentMetaData);
private:
    TagAndOptionsSettings* settings = nullptr;
    DbgLogger* dbgLogger = nullptr;
    MetaDataHelper* metaDataHelper = nullptr;
    bool showCurrentContext = true;
    QVector<QColor> ansiColors;
    //fuction should be able to both write to a qstring and a circular buffer, to place the data a lambda function must be given
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
    void processContext(CircularBufferReader *bufferReader, int begin, int end, int &releaseLength);
    void processOption(QString &optionName, int tagIndex);

    bool proccesMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i, int availabeSize, int &releaseLength);
    bool readMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i);
    bool forwardAndReadMetaData(const std::function<void (char)> &addChar, CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i, int availabeSize, int &charsAdded, int &releaseLength);
signals:
    //void propertyChanged(Property* property);
};
