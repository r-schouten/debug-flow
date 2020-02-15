#include "createconnectioncommand.h"

ConnectionCommand::ConnectionCommand(VisualConnection *connection, State _state)
{
    state = _state;
    if(state == CREATE)
    {
        setText("CREATE connection");
        state = CREATE;
        connectionUniqueId = connection->getUniqueId();
        qDebug("[debug][ConnectionCommand] constructor unique %lu", connectionUniqueId);
    }
    else
    {
        setText("DELETE connection");

        SerializationHandler handler(
        {
           .saveContext = false,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        });
        connectionJson = connection->serialize(handler);
    }
}


void ConnectionCommand::undo(FlowData *_flowData, LoadStore *loadStore)
{
    if(state == CREATE)
    {
        VisualConnection* connectionToDelete = _flowData->findConnection(connectionUniqueId);
        if(connectionToDelete == nullptr)
        {
            qFatal("[fatal][CreateConnectionCommand] connectionToDelete = nullptr");
        }

        SerializationHandler handler(
        {
           .saveContext = false,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        });
        connectionJson = connectionToDelete->serialize(handler);

        delete connectionToDelete;
        state = DELETE;
        setText("DELETE connection");

    }
    else if(state == DELETE)
    {
        DeserializationHandler handler(
        {
           .restoreContext = true,
           .restoreData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true,
       });
      loadStore->deserializeConnection(*connectionJson, handler);
      delete connectionJson;
      state = CREATE;
      setText("CREATE connection");

    }

}
