#include "visualoutputnodebase.h"

VisualOutputNodeBase::VisualOutputNodeBase()
{

}

VisualOutputNodeBase::VisualOutputNodeBase(QJsonObject &baseJson, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog)
    :VisualNodeBase(baseJson, deserializationSettings, errorLog)
{

}
