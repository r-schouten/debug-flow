#pragma once
#include "QJsonObject"
#include "commandbase.h"

#include "visualnodebase.h"
#include "nodescene.h"
#include "loadstore.h"

class NodeCommand: public CommandBase
{
public:
    enum State
    {
        DELETE,
        CREATE
    }state;
    NodeCommand(FlowObjects* _flowObjects, VisualNodeBase *node, State _state);

    void undo(LoadStore *loadStore);

private:
    int64_t nodeUniqueId;
    QJsonObject *nodeJson;
};

