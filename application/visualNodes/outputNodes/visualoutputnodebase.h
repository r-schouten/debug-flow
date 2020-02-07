#pragma once
#include "visualnodebase.h"
#include "windowmanager.h"

#include "deserialization_settings.h"
#include "serialization_error_log.h"
class VisualOutputNodeBase : public VisualNodeBase
{
protected:
    WindowManager* windowManager = nullptr;
public:
    VisualOutputNodeBase();
    VisualOutputNodeBase(QJsonObject &baseJson, DeserializationSettings_t &deserializationSettings, SerializationErrorLog &errorLog);
    virtual void setWindowManager(WindowManager* _windowManager) = 0;
signals:
    void WindowDeleted(VisualOutputNodeBase* window);



};
