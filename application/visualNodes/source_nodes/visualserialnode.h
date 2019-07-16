#pragma once

#include "serialnode.h"
#include "visualnodebase.h"

class VisualSerialNode : public VisualNodeBase
{
public:
    VisualSerialNode();

protected:
     SerialNode *node = nullptr;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

