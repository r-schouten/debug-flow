#pragma once
#include "QJsonObject"
#include "commandbase.h"

#include "visualconnection.h"
#include "nodescene.h"

class ConnectionCommand: public CommandBase
{
public:
    ConnectionCommand(VisualConnection* newConnection);
    void undo(NodeScene *scene, LoadStore *loadStore);
    CommandBase* createRedo();

private:
    uint64_t connectionUniqueId;
    QJsonObject *connectionJson;
};

