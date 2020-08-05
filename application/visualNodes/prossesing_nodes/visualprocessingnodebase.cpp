#include "visualprocessingnodebase.h"

VisualProcessingNodeBase::VisualProcessingNodeBase(FlowObjects *_flowObjects)
    :VisualNodeBase(_flowObjects)
{

}

VisualProcessingNodeBase::VisualProcessingNodeBase(FlowObjects *_flowObjects, QJsonObject &baseJson, DeserializationHandler &handler)
    :VisualNodeBase(_flowObjects, baseJson, handler)
{

}
