#pragma once

#include <QPoint>
#include <math.h>

class Utils
{
public:
    static int distanceBetweenPoints(QPoint& point1, QPoint& point2)
    {
        int deltaX = point1.x() - point2.x();
        int deltaY = point1.y() - point2.y();
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }
    static int distanceBetweenPoints(int x1, int y1, int x2, int y2)
    {
        int deltaX = x1 - x2;
        int deltaY = y1 - y2;
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }
};
