#include <QColor>

#pragma once


class NodeStyleBase
{
public:
    NodeStyleBase()
    {

    }
    QColor nodeCategoryColor;
    QColor nodeBackgroundColor = QColor::fromRgbF(0.6, 0.6, 0.6, 0.7);
};

