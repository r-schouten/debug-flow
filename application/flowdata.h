#pragma once

#include <windowmanager.h>

#include "visualnodebase.h"
#include "utils.h"

class FlowData
{
public:
    FlowData(WindowManager* _windowManager);
    ~FlowData();

    WindowManager* windowManager = nullptr;

    //list with all nodes
    QList<VisualNodeBase*> nodes;

    //hold all connections, they are not graphics items
    QList<VisualConnection*> connections;

    VisualConnection *findConnection(uint64_t uniqueId);
};

