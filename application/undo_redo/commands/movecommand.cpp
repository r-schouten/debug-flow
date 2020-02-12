#include "movecommand.h"

MoveCommand::MoveCommand(VisualNodeBase *affectedNode, QPoint previousPosition, QPoint newPosition)
    :affectedNode(affectedNode),previousPosition(previousPosition), newPosition(newPosition)
{
    setText(QString("move node %1").arg(affectedNode->name));
}

void MoveCommand::undo()
{
    affectedNode->nodePosition = previousPosition;
}
void MoveCommand::redo()
{
    affectedNode->nodePosition = newPosition;
}
bool MoveCommand::mergeWith(const QUndoCommand *other)
{
    return true;
}
