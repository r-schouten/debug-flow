#pragma once
#include <QJsonObject>

#include <serialization_settings.h>
#include <serialization_error_log.h>
class Serializable
{
public:
    virtual QJsonObject* serialize(SerializationSettings_t &serialisationSettings, SerializationErrorLog &serialisationErrorLog)=0;
};

