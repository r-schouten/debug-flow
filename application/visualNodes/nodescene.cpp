#include "nodescene.h"

#include <QGraphicsSceneMouseEvent>


NodeScene::NodeScene()
{
    QBrush brush(QColor::fromRgb(100, 100, 100));
    setBackgroundBrush(brush);
}

void NodeScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);

    QPen pen;

    pen.setColor(QColor::fromRgb(110, 110, 110));
    drawGrid(painter,rect,10,&pen);

    pen.setColor(QColor::fromRgb(125, 125, 125));
    drawGrid(painter,rect,50,&pen);

}
void NodeScene::drawGrid(QPainter * painter, const QRectF &rect, int gridSize, QPen* pen)
{
    int left = rect.left() - (int(rect.left()) % gridSize);
    int top = rect.top() - (int(rect.top()) % gridSize);

    QVarLengthArray<QLineF, 100> lines;

    for (int x = left; x < rect.right(); x += gridSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (int y = top; y < rect.bottom(); y += gridSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->setPen(*pen);
    painter->drawLines(lines.data(), lines.size());
}
