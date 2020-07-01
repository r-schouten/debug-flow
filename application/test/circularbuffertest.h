#pragma once

//contains TESTING macro
#include "main.h"

#ifdef IS_TESTING

#include <QtTest/QtTest>

#include <QObject>
#include "dbglogger.h"
#include <circularbuffer.h>

class CircularBufferTest: public QObject
{
    Q_OBJECT
    bool testContinousAppendRead(CircularBuffer *buffer, int iterations, bool printableChars, bool perByte);
public:
    CircularBufferTest();
private slots:
    void testContinousAppendRead();
    void testContinousAppendReadPerByte();
    void testContinousAppend();
    void testContionousRead();

    void testContinousAppendRead2();
};

#endif
