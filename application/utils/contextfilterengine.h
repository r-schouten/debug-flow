//Rene Schouten
//July 2019
//this class provide filter functions for tags
//tags are information hidden in the text
//also ansi escape codes can be filtered
#pragma once
#include <QStandardItemModel>
#include <QTextCharFormat>
#include <qdebug.h>
#include <qsignalmapper.h>
#include "circularbufferreader.h"
#include "ansi_types.h"
#include "tagandoptionssettings.h"

class ContextFilterEngine: public QObject
{
    Q_OBJECT

public:
    ContextFilterEngine(TagAndOptionsSettings* settings);
    bool filterData(QString *destination, CircularBufferReader *bufferReader, QTextCharFormat* format = nullptr);
    //QList<Property*> context;

private:
    TagAndOptionsSettings* settings = nullptr;
    bool showCurrentContext = false;
    //fuction should be able to both write to a qstring and a circular buffer, to place the data a lambda function must be given
    bool filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader, QTextCharFormat* format);
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
    void processContext(CircularBufferReader *bufferReader, int begin, int end);
    void processOption(QString &optionName, int tagIndex);
signals:
    //void propertyChanged(Property* property);
};
