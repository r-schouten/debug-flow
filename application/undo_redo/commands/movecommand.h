#pragma once
#include <QPoint>
#include "commandbase.h"
#include "visualnodebase.h"

class VisualNodeBase;
class MoveCommand: public CommandBase
{
public:
    MoveCommand(VisualNodeBase* affectedNode,QPoint previousPosition, QPoint newPosition);
    virtual void undo();
    virtual void redo();
    virtual bool mergeWith(const QUndoCommand *other);
    VisualNodeBase* affectedNode = nullptr;

private:
    QPoint previousPosition;
    QPoint newPosition;
};

