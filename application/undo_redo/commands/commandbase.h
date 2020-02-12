#pragma once
#include <QUndoCommand>

//#include "nodescene.h"
//#include "loadstore.h"

class LoadStore;
class NodeScene;
class CommandBase : public QUndoCommand
{
protected:
    NodeScene* nodeScene = nullptr;
    LoadStore* loadStore = nullptr;

public:
    void setUtils(NodeScene* scene, LoadStore* loadStore);

};
