#pragma once
#include <QTextBlockUserData>
#include "metadatahelper.h"
class TextBlockWithMetaData : public QTextBlockUserData
{
public:
    TextBlockWithMetaData();
    int blockNr;
    MetaData_t metaData;
};

