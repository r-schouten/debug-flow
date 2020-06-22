#pragma once
#include <QPoint>
#include "commandbase.h"

#include "visualnodebase.h"
#include "nodescene.h"
#include "loadstore.h"
class MoveCommand: public CommandBase
{
public:
    MoveCommand(FlowObjects* _flowObjects, VisualNodeBase* affectedNode,QPoint previousPosition, QPoint newPosition);
    void undo(LoadStore *loadStore);

private:
    QPoint previousPosition;
    QPoint newPosition;
    int64_t affectedNodeId;
};

