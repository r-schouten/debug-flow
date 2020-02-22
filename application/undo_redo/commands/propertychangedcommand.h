#pragma once
#include "QJsonObject"
#include "commandbase.h"

#include "nodescene.h"
#include "loadstore.h"

#include "nodesettingsbase.h"

class PropertyChangedCommand: public CommandBase
{
public:
    PropertyChangedCommand(NodeSettingsBase *nodeSettings);
    ~PropertyChangedCommand();

    void undo(FlowData *_flowData, LoadStore *loadStore);

private:
    QJsonObject *settingsJson = nullptr;
    NodeSettingsBase* nodeSettings = nullptr;
};

