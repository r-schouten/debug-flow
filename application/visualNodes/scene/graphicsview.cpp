#include "graphicsview.h"

#include <visualnodebase.h>

GraphicsView::GraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    selectionManager = SelectionManager::getInstance();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setMouseTracking(true);

    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setDragMode(QGraphicsView::RubberBandDrag);

    connect(this,SIGNAL(rubberBandChanged(QRect, QPointF, QPointF)),this,SLOT(selectionUpdate(QRect, QPointF, QPointF)));
}
void GraphicsView::selectionUpdate(QRect rubberBandRect, QPointF fromScenePoint, QPointF toScenePoint)
{
    QList<QGraphicsItem*> selectedItems = items(rubberBandRect,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
    QListIterator<QGraphicsItem*> iterator(selectedItems);
    if(iterator.hasNext())
    {
        selectionManager->clearSelected();
    }
    while(iterator.hasNext())
    {
        VisualNodeBase* node = dynamic_cast<VisualNodeBase*>(iterator.next());
        if(node)
        {
            qDebug("selectionUpdate");

            selectionManager->setSelected(node, false);
        }
    }
    //the update flag is used in nodescene.cpp to move to prevent deselection of items when clicked on a node, it's also used to move selected nodes
    //clear to flag to prevent the nodescene to move nodes after the selection
    selectionManager->clearUpdateFlag();
}
int _numScheduledScalings = 0;
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
     int numSteps = numDegrees / 15; // see QWheelEvent documentation
     _numScheduledScalings += numSteps;
     if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
     _numScheduledScalings = numSteps;

     QTimeLine *anim = new QTimeLine(350, this);
     anim->setUpdateInterval(30);

     connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
     connect(anim, SIGNAL (finished()), SLOT (animFinished()));
     anim->start();
}
qreal minScale = 0.5;
qreal maxScale = 2;

void GraphicsView::scalingTime(qreal x)
{
    QTransform matrix = transform();
    if((matrix.m11() < maxScale || _numScheduledScalings < 0) && (matrix.m11() > minScale || _numScheduledScalings > 0))
    {
        qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
        scale(factor, factor);
    }
}
void GraphicsView::animFinished()
{
    if (_numScheduledScalings > 0)
    _numScheduledScalings--;
    else
    _numScheduledScalings++;
    sender()->~QObject();
}
