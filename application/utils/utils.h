#pragma once

#include "dbglogger.h"

#include <QJsonDocument>
#include <QLineF>
#include <QPoint>
#include <QRandomGenerator64>
#include <math.h>

class Utils
{
public:
    static int distanceBetweenPoints(QPointF& point1, QPointF& point2)
    {
        int deltaX = point1.x() - point2.x();
        int deltaY = point1.y() - point2.y();
        return sqrt(deltaX*deltaX + deltaY*deltaY);
    }
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
    static qreal dist(const QPointF &p, const QLineF &line)
    {
      // transform to loocal coordinates system (0,0) - (lx, ly)
      QPointF p1 = line.p1();
      QPointF p2 = line.p2();
      qreal x = p.x() - p1.x();
      qreal y = p.y() - p1.y();
      qreal x2 = p2.x() - p1.x();
      qreal y2 = p2.y() - p1.y();

      // if line is a point (nodes are the same) =>
      // just return distance between point and one line node
      qreal norm = sqrt(x2*x2 + y2*y2);
      if (norm <= std::numeric_limits<int>::epsilon())
        return sqrt(x*x + y*y);

      // distance
      return fabs(x*y2 - y*x2) / norm;
    }
    static QRandomGenerator randomGenerator;
    static int64_t getRandom()
    {
        //json supports no unsigned 32 bits, therefore 31 bits
        return randomGenerator.bounded(pow(2,31));
    }
    static void printJson(QJsonObject* object, DbgLogger* dbglogger)
    {
        QJsonDocument doc(*object);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        dbglogger->debug("utils",__FUNCTION__,strJson.toStdString().c_str());
    }
};
