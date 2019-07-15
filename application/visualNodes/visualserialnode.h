#pragma once


#include "visualnodebase.h"
class VisualSerialNode : public VisualNodeBase
{
public:
    VisualSerialNode();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

