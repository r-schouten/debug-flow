#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>
class CircularBufferVisualisation : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CircularBufferVisualisation(QWidget *parent = nullptr);


    void updatePie(int _capacity, int _head, int _iteration, int _tail, int _tailIteration);
protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
    const int SIZE = 1000;

    int capacity = 100;
    int head = 0;
    int iteration = 0;
    int tail = 0;
    int tailIteration = 0;
};
