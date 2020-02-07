#include "visualoutputnodebase.h"

VisualOutputNodeBase::VisualOutputNodeBase()
{

}

VisualOutputNodeBase::VisualOutputNodeBase(QJsonObject &baseJson, DeserializationHandler &handler)
    :VisualNodeBase(baseJson, handler)
{

}
