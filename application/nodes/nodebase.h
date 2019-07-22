#pragma once
class NodeBase
{
public:
    NodeBase();
    virtual void activate(){};
    bool hasInput = false;
    bool hasOutput = false;
};

