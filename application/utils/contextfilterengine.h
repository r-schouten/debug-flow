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
class ContextFilterEngine: public QObject
{
    Q_OBJECT

public:
    ContextFilterEngine(TagAndOptionsSettings* settings, DbgLogger *dbgLogger);

    void filterData(const std::function<void (char)> &addChar, CircularBufferReader *bufferReader, int sourceAvailable, int destinationAvailabe, bool *allDataProcessed, MetaData_t *currentMetaData);
    void filterDataWithStyle(const std::function<void(char)>& addCharLambda, const std::function<void()>& styleChangedLambda, CircularBufferReader *bufferReader, QTextCharFormat *format, MetaData_t* currentMetaData);
private:
    TagAndOptionsSettings* settings = nullptr;
    DbgLogger* dbgLogger = nullptr;
    MetaDataHelper* metaDataHelper = nullptr;
    bool showCurrentContext = true;
    //fuction should be able to both write to a qstring and a circular buffer, to place the data a lambda function must be given
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
    void processContext(CircularBufferReader *bufferReader, int begin, int end, int &releaseLength);
    bool proccesMetaData(CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i, int availabeSize, int &releaseLength);
    void processOption(QString &optionName, int tagIndex);
    bool forwardMetaData(const std::function<void (char)> &addChar, CircularBufferReader *bufferReader, MetaData_t *currentMetaData, int &i, int availabeSize, int &charsAdded, int &destinationAvailabe, int &releaseLength);
signals:
    //void propertyChanged(Property* property);
};
