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

class PropertyOption: public QObject
{
public:
    PropertyOption(QString name,bool enabled)
        :name(name),enabled(enabled){}
    QString name;
    virtual bool getEnabled()
    {
        if(standardItem!=nullptr)
        {
            return standardItem->checkState();
        }
        return enabled;
    };
    virtual void setEnabled(bool enabled)
    {
        if(standardItem!=nullptr)
        {
            if(enabled)
            {
                standardItem->setCheckState(Qt::Checked);
            }
            else {
                standardItem->setCheckState(Qt::Unchecked);
            }
        }
        else
        {
            enabled = true;
        }

    }
    QStandardItem* standardItem = nullptr;
private:
    bool enabled;

};

class Property
{
public:
    QList<PropertyOption*> options;
    QStandardItemModel* itemModel = nullptr;
public:
    PropertyOption* getOption(QString OptionName)
    {
        QListIterator<PropertyOption*> iterator(options);
        while(iterator.hasNext())
        {
            PropertyOption* option = iterator.next();
            if(option->name.compare(OptionName) == 0)
            {
                return option;
            }
        }
        return nullptr;
    }
};

class ContextFilter: public QObject
{
    Q_OBJECT

public:
    ContextFilter();
    bool filterData(QString *destination, CircularBufferReader *bufferReader, QTextCharFormat* format);
    QList<Property*> context;

private:
    bool keepContext = true;
    bool showCurrentContext = false;
    //fuction should be able to both write to a qstring and a circular buffer, to place the data a lambda function must be given
    bool filterData(const std::function<void (char)> &addChar, const std::function<bool ()> &deleteCarageReturnLambda, CircularBufferReader *bufferReader, QTextCharFormat* format);
    bool processANSIEscape(CircularBufferReader *bufferReader, QTextCharFormat *format, int beginIndex, int endIndex);
    void applyANSICode(QTextCharFormat *format, ANSICode ansiCode);
    void processContext(CircularBufferReader *bufferReader, int begin, int end);
    void processproperty(QString &propery, int propertyIndex);
signals:
    void propertyChanged(Property* property);
};
