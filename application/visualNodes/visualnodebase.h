#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "nodebase.h"
class VisualNodeBase : public QGraphicsItem
{
protected:
    int x = 100;
    int y = 100;
    const int width = 100;
    const int height = 50;

    int connectionDiameter = 10;

public:
    VisualNodeBase();

    QRectF boundingRect() const;
    QRectF innerRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    // QGraphicsItem interface
    QRectF getLeftConnection();
    QRectF getRightConnection();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void paintBase(QPainter *painter, QColor baseColor, QString name);
    void drawConnectionLeft(QPainter *painter);
    void drawConnectionRight(QPainter *painter);

    static QList<VisualNodeBase*> selectedItems;
    bool isSelected();

};

