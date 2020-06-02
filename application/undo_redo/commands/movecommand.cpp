#include "movecommand.h"

MoveCommand::MoveCommand(VisualNodeBase *affectedNode, QPoint previousPosition, QPoint newPosition)
    :previousPosition(previousPosition), newPosition(newPosition)
{
    affectedNodeId = affectedNode->getUniqueId();

    setText(QString("move node %1").arg(affectedNode->name));

    qDebug("[debug][MoveCommand] affectedNodeId %lld", affectedNodeId);

}
void MoveCommand::undo(FlowData *_flowData, LoadStore *loadStore)
{
    Q_UNUSED(loadStore);
    VisualNodeBase* affectedNode = _flowData->findnode(affectedNodeId);
    if(affectedNode == nullptr)
    {
        qFatal("[debug][MoveCommand] affected node = nullptr");
    }
    auto temp = affectedNode->nodePosition;
    affectedNode->nodePosition = previousPosition;
    previousPosition = temp;
}

