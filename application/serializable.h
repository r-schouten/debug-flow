#pragma once
#include <QJsonObject>

class Serializable
{
public:
    virtual QJsonObject* serialize()=0;
};

