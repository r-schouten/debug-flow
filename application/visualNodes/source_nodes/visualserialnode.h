#pragma once

#include "serialnode.h"
#include "sourcestyle.h"
#include "visualnodebase.h"

class VisualSerialNode : public VisualNodeBase, public SourceStyle
{
        Q_OBJECT
public:
    VisualSerialNode();
    VisualNodeBase *clone();

protected:
     SerialNode *node = nullptr;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

