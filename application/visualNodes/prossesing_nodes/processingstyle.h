#pragma once
#include "nodestylebase.h"

class ProcessingStyle : public NodeStyleBase
{
public:
    ProcessingStyle()
    {
        nodeCategoryColor = QColor::fromRgbF(0.7, 0.3, 0.7, 0.7);
    }
};

