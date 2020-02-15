#pragma once
#include <QPoint>
#include "commandbase.h"
#include "visualnodebase.h"

class VisualNodeBase;
class MoveCommand: public CommandBase
{
public:
    MoveCommand(VisualNodeBase* affectedNode,QPoint previousPosition, QPoint newPosition);
    void undo(FlowData *_flowData, LoadStore *loadStore);

    VisualNodeBase* affectedNode = nullptr;

private:
    QPoint previousPosition;
    QPoint newPosition;
};

