#include "createnodecommand.h"

NodeCommand::NodeCommand(VisualNodeBase *node, State _state)
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
        });
        nodeJson = LoadStore::serializeNode(node, handler);
    }
}


void NodeCommand::undo(FlowData *_flowData, LoadStore *loadStore)
{
    if(state == CREATE)
    {
        VisualNodeBase* nodeToDelete = _flowData->findnode(nodeUniqueId);
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
        });
        nodeJson = loadStore->serializeNode(nodeToDelete, handler);
        Utils::printJson(nodeJson);
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
       });
       Utils::printJson(nodeJson);

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
