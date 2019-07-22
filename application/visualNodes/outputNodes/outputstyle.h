#pragma once
#include "nodestylebase.h"


class OutputStyle : public NodeStyleBase
{
public:
    OutputStyle()
    {
         nodeCategoryColor = QColor::fromRgbF(0.3, 0.7, 0.7, 0.7);
    }
};

