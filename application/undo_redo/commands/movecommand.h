#pragma once
#include <QPoint>
#include "commandbase.h"
#include "visualnodebase.h"

#include "flowdata.h"

class VisualNodeBase;
class MoveCommand: public CommandBase
{
public:
    MoveCommand(VisualNodeBase* affectedNode,QPoint previousPosition, QPoint newPosition);
    void undo(FlowData *_flowData, LoadStore *loadStore);

private:
    QPoint previousPosition;
    QPoint newPosition;
    int64_t affectedNodeId;
};

