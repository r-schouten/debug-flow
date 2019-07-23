#pragma once

#include "serialnode.h"
#include "sourcestyle.h"
#include "visualnodebase.h"
#include "selectionmanager.h"
#include "visualsourcenodebase.h"

#include <QGraphicsProxyWidget>

class VisualSerialNode : public VisualSourceNodeBase
{
        Q_OBJECT
public:
    VisualSerialNode();
    VisualNodeBase *clone();

    ~VisualSerialNode();
    void activate();

protected:
     SerialNode *node = nullptr;
    QGraphicsProxyWidget* proxyWidget = nullptr;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

