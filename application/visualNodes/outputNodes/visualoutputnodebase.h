#pragma once
#include "visualnodebase.h"
#include "windowmanager.h"

#include "deserialization_handler.h"

class VisualOutputNodeBase : public VisualNodeBase
{
protected:
    WindowManager* windowManager = nullptr;
public:
    VisualOutputNodeBase();
    VisualOutputNodeBase(QJsonObject &baseJson, DeserializationHandler &handler);
    virtual void setWindowManager(WindowManager* _windowManager) = 0;
signals:
    void WindowDeleted(VisualOutputNodeBase* window);

};
