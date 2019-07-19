#pragma once
#include <QPainter>

enum PathStyle
{
    LINE,
    BEZIER_STRAIGT,
    BEZIER
};
class ConnectionStyle
{
public:
    ConnectionStyle(){};
    QColor lineColor = QColor::fromRgbF(1,1,1,0.7);
    QColor selectedColor = QColor::fromRgbF(0.2,0.7,1,0.6);
    QBrush brush = QBrush(Qt::NoBrush);
    int lineWidth = 8;
    PathStyle pathStyle = PathStyle::BEZIER_STRAIGT;
    int intersectMargin = 10;
};

