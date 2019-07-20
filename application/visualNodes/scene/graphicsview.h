#pragma once
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>

#include "selectionmanager.h"
#include "nodebase.h"
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
    SelectionManager* selectionManager = nullptr;
public slots:
    void scalingTime(qreal x);
    void animFinished();
    void selectionUpdate(QRect rubberBandRect, QPointF fromScenePoint, QPointF toScenePoint);
};



