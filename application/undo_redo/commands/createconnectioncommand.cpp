#include "createconnectioncommand.h"

//NodeScene and Loadstore can not be used in the costructor because they are not initialized yet
CreateConnectionCommand::CreateConnectionCommand(VisualConnection *_connection)
{
    setText("create connetion");
    connection = _connection;
    SerializationSettings_t settings;
    SerializationHandler serializationHandler(settings);
    connectionJson = connection->serialize(serializationHandler);
}
CreateConnectionCommand::~CreateConnectionCommand()
{
    qDebug("[debug][DeleteConnectionCommand] destructor called");
    delete connectionJson;
}
void CreateConnectionCommand::undo()
{
    delete connection;
    connection = nullptr;
}
void CreateConnectionCommand::redo()
{
//    DeserializationSettings_t settings;
//    DeserializationHandler handler(settings);
//    connection = loadStore->deserializeConnection(*connectionJson, handler);
}

