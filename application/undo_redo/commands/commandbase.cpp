#include "commandbase.h"


int CommandBase::getId() const
{
    return id;
}

void CommandBase::setId(int value)
{
    id = value;
}