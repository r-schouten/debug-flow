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
        selectedBorderPen.setWidth(3);

        borderPen = QColor::fromRgbF(0.3, 0.3, 0.3, 0.7);
        borderPen.setWidth(3);

        titlePen = QColor::fromRgbF(1, 1, 1, 1);
        titleFont.setPointSize(10);
        titleFont.setBold(true);

        textPen = QColor::fromRgbF(1, 1, 1, 1);
        textFont.setPointSize(8);

        errorPen = QColor::fromRgbF(1, 0, 0, 1);
    }
    QColor nodeCategoryColor;
    QColor nodeBackgroundColor = QColor::fromRgbF(0.6, 0.6, 0.6, 0.7);
    QPen connectorPen;
    QBrush connectorBrush;

    QPen selectedBorderPen;
    QPen borderPen;

    QPen titlePen;
    QFont titleFont;

    QPen textPen;
    QFont textFont;

    QPen errorPen;


};

