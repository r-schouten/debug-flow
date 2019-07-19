#pragma once
#include <QPainter>

class NodeStyleBase
{
public:
    NodeStyleBase()
    {
        connectorPen = QColor::fromRgbF(0.6, 0.6, 0.6, 0.7);
        connectorBrush = QColor::fromRgbF(1, 1, 1, 0.7);

        selectedBorderPen = QColor::fromRgbF(0.2, 0.6, 0.7, 0.7);
        borderPen = QColor::fromRgbF(0.3, 0.3, 0.3, 0.7);

        titlePen = QColor::fromRgbF(1, 1, 1, 1);
        titleFont.setPointSize(10);
        titleFont.setBold(true);
    }
    QColor nodeCategoryColor;
    QColor nodeBackgroundColor = QColor::fromRgbF(0.6, 0.6, 0.6, 0.7);
    QPen connectorPen;
    QBrush connectorBrush;

    QPen selectedBorderPen;
    QPen borderPen;

    QPen titlePen;
    QFont titleFont;

};

