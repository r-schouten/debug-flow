#pragma once
#include <QUndoCommand>

//#include "nodescene.h"
//#include "loadstore.h"

#include <QListWidgetItem>
class FlowData;
class LoadStore;
class NodeScene;
class CommandBase : public QListWidgetItem
{
private:
    int id = 0;
public:
    virtual void undo(FlowData* _flowData, LoadStore* loadStore)=0;
    //virtual CommandBase* createRedo() = 0;
    int getId() const;
    void setId(int value);
};
