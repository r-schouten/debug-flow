#pragma once
#include "nodestylebase.h"

class SourceStyle : public NodeStyleBase
{
public:
    SourceStyle()
    {
        nodeCategoryColor = QColor::fromRgbF(0.7, 0.7, 0.3, 0.7);
    }
};
