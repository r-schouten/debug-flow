#include "createconnectioncommand.h"

ConnectionCommand::ConnectionCommand(FlowObjects* _flowObjects, VisualConnection *connection, State _state)
    :CommandBase(_flowObjects)
{
    state = _state;
    if(state == CREATE)
    {
        setText("CREATE connection");
        state = CREATE;
        connectionUniqueId = connection->getUniqueId();
        flowObjects->getDbgLogger()->debug("ConnectionCommand",__FUNCTION__,"constructor unique %lld", connectionUniqueId);
    }
    else
    {
        setText("DELETE connection");

        SerializationHandler handler(
        {
           .saveContext = true,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        }, flowObjects->getDbgLogger());
        connectionJson = connection->serialize(handler);
    }
}

void ConnectionCommand::undo(LoadStore *loadStore)
{
    if(state == CREATE)
    {
        VisualConnection* connectionToDelete = flowObjects->findConnection(connectionUniqueId);
        if(connectionToDelete == nullptr)
        {
            qFatal("[fatal][ConnectionCommand] connectionToDelete = nullptr");
        }

        SerializationHandler handler(
        {
           .saveContext = true,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        }, flowObjects->getDbgLogger());
        connectionJson = connectionToDelete->serialize(handler);

        connectionToDelete->setDeleteReason(VisualConnection::DeleteReason::UNDO_REDO);
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
       },flowObjects->getDbgLogger());
      VisualConnection* recoveredConnection = loadStore->deserializeConnection(*connectionJson, handler);
      if(recoveredConnection == nullptr)
      {
          qFatal("[fatal][ConnectionCommand] recoveredConnection = nullptr");
      }
      connectionUniqueId = recoveredConnection->getUniqueId();
      delete connectionJson;
      state = CREATE;
      setText("CREATE connection");

    }

}
