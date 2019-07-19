#pragma once
#include <QPainter>
#include <QColor>
enum PathStyle
{
    LINE,
    BEZIER_STRAIGT,
    BEZIER
};
class ConnectionStyle
{
public:
    ConnectionStyle(){
        endsPen.setColor(QColor::fromRgbF(0.8,0.1,0.5,0.6));
        endsPen.setWidth(2);
        endsPenNotConnected.setColor(QColor::fromRgbF(1,1,1,0.7));
        endsPenNotConnected.setWidth(2);

        linePen.setWidth(lineWidth);
        selectedPen.setWidth(lineWidth);
    }
    QPen linePen = QColor::fromRgbF(1,1,1,0.7);
    QPen selectedPen = QColor::fromRgbF(0.2,0.7,1,0.6);
    QBrush brush = QBrush(Qt::NoBrush);
    QPen endsPen;
    QPen endsPenNotConnected;
    int lineWidth = 8;
    PathStyle pathStyle = PathStyle::BEZIER_STRAIGT;
    int intersectMargin = 10;
};

