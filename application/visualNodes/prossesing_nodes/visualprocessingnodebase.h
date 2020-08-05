#pragma once
#include "visualnodebase.h"
#include "windowmanager.h"

#include "deserialization_handler.h"

class VisualProcessingNodeBase : public VisualNodeBase
{
public:
    VisualProcessingNodeBase(FlowObjects *_flowObjects);
    VisualProcessingNodeBase(FlowObjects *_flowObjects, QJsonObject &baseJson, DeserializationHandler &handler);

};
