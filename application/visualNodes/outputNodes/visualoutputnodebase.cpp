#include "visualoutputnodebase.h"

VisualOutputNodeBase::VisualOutputNodeBase(FlowObjects *_flowObjects)
    :VisualNodeBase(_flowObjects)
{

}

VisualOutputNodeBase::VisualOutputNodeBase(FlowObjects *_flowObjects, QJsonObject &baseJson, DeserializationHandler &handler)
    :VisualNodeBase(_flowObjects, baseJson, handler)
{

}
