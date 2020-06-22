#pragma once
#include "QJsonObject"
#include "commandbase.h"

#include "visualconnection.h"
#include "nodescene.h"
#include "loadstore.h"

class ConnectionCommand: public CommandBase
{
public:
    enum State
    {
        DELETE,
        CREATE
    }state;
    ConnectionCommand(FlowObjects* _flowObjects, VisualConnection *object, State _state);

    void undo(LoadStore *loadStore);

private:
    int64_t connectionUniqueId;
    QJsonObject *connectionJson;
};

