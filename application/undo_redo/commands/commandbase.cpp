#include "commandbase.h"


CommandBase::CommandBase(FlowObjects *_flowObjects)
    :flowObjects(_flowObjects)
{

}

int CommandBase::getId() const
{
    return id;
}

void CommandBase::setId(int value)
{
    id = value;
}
