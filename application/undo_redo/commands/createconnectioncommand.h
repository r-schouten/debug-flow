#pragma once
#include "commandbase.h"

//#include "visualconnection.h"
#include "nodescene.h"
#include "loadstore.h"

class VisualConnection;
class CreateConnectionCommand: public CommandBase
{
public:
    CreateConnectionCommand(VisualConnection *_connection);
    ~CreateConnectionCommand();

    void undo();
    void redo();
private:
    QJsonObject *connectionJson;
    VisualConnection* connection = nullptr;
};

