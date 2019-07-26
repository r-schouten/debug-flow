#pragma once
#include <QObject>
//https://en.wikipedia.org/wiki/ANSI_escape_code
enum class ANSIType
{
    NONE,
    UNKNOWN,
    FORMATTING,
    EREASE,
    CURSOR,
    SCREENMODE,
    ERROR
};
struct ANSICode
{
    ANSIType type = ANSIType::NONE;
    int value = 0;
};
struct ANSICodes
{
    QList<ANSICode> code;
    bool found = false;
};
