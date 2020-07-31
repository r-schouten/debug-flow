#pragma once
#include <QTextBlockUserData>
#include "timestamphelper.h"
class TextBlockWithTimestamp : public QTextBlockUserData
{
public:
    TextBlockWithTimestamp();
    int blockNr;
    TimeStamp_t timestamp;
};

