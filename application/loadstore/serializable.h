#pragma once
#include <QJsonObject>

#include <serialization_settings.h>
#include <serialization_handler.h>
class Serializable
{
public:
    virtual QJsonObject* serialize(SerializationSettings_t &serialisationSettings, SerializationHandler &serialisationErrorLog)=0;
};

