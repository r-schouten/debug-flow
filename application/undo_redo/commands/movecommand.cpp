#include "movecommand.h"

MoveCommand::MoveCommand(VisualNodeBase *affectedNode, QPoint previousPosition, QPoint newPosition)
    :affectedNode(affectedNode),previousPosition(previousPosition), newPosition(newPosition)
{
    setText(QString("move node %1").arg(affectedNode->name));

}
void MoveCommand::undo(FlowData *_flowData, LoadStore *loadStore)
{
    auto temp = affectedNode->nodePosition;
    affectedNode->nodePosition = previousPosition;
    previousPosition = temp;
}

