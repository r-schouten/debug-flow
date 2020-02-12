#pragma once
#include "commandbase.h"

//#include "visualconnection.h"
#include "nodescene.h"
#include "loadstore.h"

class VisualConnection;
class DeleteConnectionCommand: public CommandBase
{
public:
    DeleteConnectionCommand(VisualConnection *connection);
    ~DeleteConnectionCommand();

    void undo();
    void redo();
private:
    QJsonObject *connectionJson;
    VisualConnection* oldConnection = nullptr;
};

