#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "nodebase.h"
class VisualNodeBase : public QGraphicsItem
{
protected:
    NodeBase *node = nullptr;
    int x = 100;
    int y = 100;
    const int width = 100;
    const int height = 50;
public:
    VisualNodeBase();

    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

