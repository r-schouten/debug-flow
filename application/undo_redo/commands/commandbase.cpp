#include "commandbase.h"


void CommandBase::setUtils(NodeScene *_scene, LoadStore *_loadStore)
{
    loadStore = _loadStore;
    nodeScene = _scene;
}
