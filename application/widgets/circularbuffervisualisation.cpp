#include "circularbuffervisualisation.h"

CircularBufferVisualisation::CircularBufferVisualisation(QWidget *parent) : QGraphicsScene(parent)
{
}

void CircularBufferVisualisation::updatePie(int _capacity, int _head, int _iteration, int _tail, int _tailIteration)
{
    capacity = _capacity;
    head = _head;
    iteration = _iteration;
    tail = _tail;
    tailIteration = _tailIteration;

    update(sceneRect());
}

void CircularBufferVisualisation::drawForeground(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::green);
    painter->drawEllipse(rect);


    int beginPos = ((double)tail/capacity) * -360*16 +90*16;
    int endPos = ((double)head/capacity) * -360*16 +90*16;
    if(tail == INT_MAX)
    {
        beginPos = 90*16;
    }
    painter->setBrush(Qt::red);
    painter->drawPie(rect,beginPos,endPos-beginPos);
}
