#include "createnodecommand.h"

NodeCommand::NodeCommand(FlowObjects* _flowObjects, VisualNodeBase *node, State _state)
    :CommandBase(_flowObjects)
{
    state = _state;
    if(state == CREATE)
    {
        setText("CREATE node");
        state = CREATE;
        nodeUniqueId = node->getUniqueId();
    }
    else
    {
        setText("DELETE node");
        SerializationHandler handler(
        {
           .saveContext = true,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        }, flowObjects->getDbgLogger());
        nodeJson = LoadStore::serializeNode(node, handler);
    }
}


void NodeCommand::undo(LoadStore *loadStore)
{
    if(state == CREATE)
    {
        VisualNodeBase* nodeToDelete = flowObjects->findnode(nodeUniqueId);
        if(nodeToDelete == nullptr)
        {
            qFatal("[fatal][NodeCommand] connectionToDelete = nullptr");
        }


        SerializationHandler handler(
        {
           .saveContext = true,
           .saveData = false,
           .saveTempData = false,
           .exceptionOnError = true,
           .exceptionOnFatal = true
        }, flowObjects->getDbgLogger());
        nodeJson = loadStore->serializeNode(nodeToDelete, handler);
        Utils::printJson(nodeJson, flowObjects->getDbgLogger());
        delete nodeToDelete;
        state = DELETE;
        setText("DELETE node");

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
       Utils::printJson(nodeJson, flowObjects->getDbgLogger());

      VisualNodeBase * recoveredNode = loadStore->deserializeNode(*nodeJson, handler);
      if(recoveredNode == nullptr)
      {
          qFatal("[fatal][NodeCommand] recoveredNode = nullptr");
      }
      nodeUniqueId = recoveredNode->getUniqueId();

      delete nodeJson;
      state = CREATE;
      setText("CREATE node");

    }

}
