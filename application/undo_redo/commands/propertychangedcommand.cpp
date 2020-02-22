#include "propertychangedcommand.h"

PropertyChangedCommand::PropertyChangedCommand(NodeSettingsBase* nodeSettings)
    :nodeSettings(nodeSettings)
{
    setText("node settings changed");

    SerializationHandler handler(
    {
       .saveContext = false,
       .saveData = false,
       .saveTempData = false,
       .exceptionOnError = true,
       .exceptionOnFatal = true
    });
    settingsJson = nodeSettings->serialize(handler);
}
PropertyChangedCommand::~PropertyChangedCommand()
{
    if(settingsJson != nullptr)
    {
        delete settingsJson;
    }
}

void PropertyChangedCommand::undo(FlowData *_flowData, LoadStore *loadStore)
{
    DeserializationHandler dHandler(
    {
       .restoreContext = true,
       .restoreData = false,
       .exceptionOnError = true,
       .exceptionOnFatal = true,
   });
    SerializationHandler sHandler(
    {
       .saveContext = false,
       .saveData = false,
       .saveTempData = false,
       .exceptionOnError = true,
       .exceptionOnFatal = true
    });

    QJsonObject* newSettings = nodeSettings->serialize(sHandler);

    nodeSettings->deserialize(*settingsJson, dHandler);

    delete settingsJson;
    settingsJson = newSettings;
}
