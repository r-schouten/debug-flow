#pragma once
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>

#include "selectionmanager.h"
#include "flowobjects.h"
#include "nodebase.h"
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent);
    void setData(FlowObjects* _flowObjects, NodeScene* _nodeScene);
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    SelectionManager* selectionManager = nullptr;
    DbgLogger* dbgLogger = nullptr;
    bool scrollButtonHold = false;
    QPointF lastMousePosition;
public slots:
    void scalingTime(qreal x);
    void animFinished();
    void selectionUpdate(QRect rubberBandRect, QPointF fromScenePoint, QPointF toScenePoint);

};



