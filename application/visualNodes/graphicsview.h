#pragma once
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
public slots:
    void scalingTime(qreal x);
    void animFinished();
};



