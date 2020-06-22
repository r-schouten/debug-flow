#include "movecommand.h"

MoveCommand::MoveCommand(FlowObjects* _flowObjects, VisualNodeBase *affectedNode, QPoint previousPosition, QPoint newPosition)
    :CommandBase(_flowObjects),previousPosition(previousPosition), newPosition(newPosition)
{
    affectedNodeId = affectedNode->getUniqueId();

    setText(QString("move node %1").arg(affectedNode->name));

    flowObjects->getDbgLogger()->debug("MoveCommand",__FUNCTION__,"affectedNodeId %lld", affectedNodeId);

}
void MoveCommand::undo(LoadStore *loadStore)
{
    Q_UNUSED(loadStore);
    VisualNodeBase* affectedNode = flowObjects->findnode(affectedNodeId);
    if(affectedNode == nullptr)
    {
        qFatal("[debug][MoveCommand] affected node = nullptr");
    }
    auto temp = affectedNode->nodePosition;
    affectedNode->nodePosition = previousPosition;
    previousPosition = temp;
}

