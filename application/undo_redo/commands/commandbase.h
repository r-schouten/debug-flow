#pragma once

//#include "nodescene.h"
//#include "loadstore.h"

#include <QListWidgetItem>
#include "flowobjects.h"

class FlowObjects;
class LoadStore;
class NodeScene;
class CommandBase : public QListWidgetItem
{
private:
    int id = 0;
protected:
    FlowObjects* flowObjects = nullptr;
public:
    CommandBase(FlowObjects* _flowObjects);
    virtual void undo( LoadStore* loadStore)=0;
    //virtual CommandBase* createRedo() = 0;
    int getId() const;
    void setId(int value);
};
