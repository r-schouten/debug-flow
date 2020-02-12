#include "deleteconnectioncommand.h"

//NodeScene and Loadstore can not be used in the costructor because they are not initialized yet
DeleteConnectionCommand::DeleteConnectionCommand(VisualConnection *connection)
{
    setText("delete connetion");
    SerializationSettings_t settings;
    SerializationHandler serializationHandler(settings);
    connectionJson = connection->serialize(serializationHandler);

}
DeleteConnectionCommand::~DeleteConnectionCommand()
{
    qDebug("[debug][DeleteConnectionCommand] destructor called");
    delete connectionJson;
}
void DeleteConnectionCommand::undo()
{
    DeserializationSettings_t settings;
    DeserializationHandler handler(settings);
    oldConnection = loadStore->deserializeConnection(*connectionJson, handler);
}
void DeleteConnectionCommand::redo()
{
    delete oldConnection;
}

