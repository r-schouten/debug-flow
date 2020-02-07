#pragma once
#include <QJsonObject>

#include <serialization_handler.h>
#include <deserialization_handler.h>
class Serializable
{
public:
    virtual QJsonObject* serialize(SerializationHandler &handler)=0;
};

