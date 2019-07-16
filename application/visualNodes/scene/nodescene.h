#pragma once
#include <QGraphicsScene>
#include <QPainter>
class NodeScene:public QGraphicsScene
{
public:
    NodeScene();


private:
    void drawGrid(QPainter *painter, const QRectF &rect, int gridSize, QPen *pen);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

