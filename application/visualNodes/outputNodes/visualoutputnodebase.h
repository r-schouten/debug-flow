#pragma once
#include "visualnodebase.h"
#include "windowmanager.h"
class VisualOutputNodeBase : public VisualNodeBase
{
protected:
    WindowManager* windowManager = nullptr;
public:
    VisualOutputNodeBase();
    virtual void setWindowManager(WindowManager* _windowManager) = 0;
signals:
    void WindowDeleted(VisualOutputNodeBase* window);



};
