#include "flowwidget.h"

FlowWidget::FlowWidget(QWidget *parent) : QWidget(parent)
{
    flow_ui = new Ui_flowWidget();
    flow_ui->setupUi(this);
    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    propertyWidgetManager = new PropertyWidgetManager(flow_ui->propertiesWidget,flow_ui->rightTabWidget);

    SelectionManager::getInstance()->setPropertyWidgetManager(propertyWidgetManager);

    windowManager = new WindowManager(flow_ui->mdiArea);

    flowData = new FlowData(windowManager);

    undoRedoManager = new UndoRedoManager(flow_ui->undoRedoWidget);

    nodeScene = new NodeScene(flowData, undoRedoManager);

    loadStore = new LoadStore(flowData, nodeScene);
    fileSystem = new FileSystem();
    undoRedoManager->setData(flowData, loadStore);


    flow_ui->graphicsView->setScene(nodeScene);

    itemsList = new ItemList(flow_ui->resourceList,nodeScene);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &FlowWidget::updateUI);
    UiUpdatetimer->start(30);
    flow_ui->graphicsView->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);
}
FlowWidget::~FlowWidget()
{
    delete UiUpdatetimer;

    delete itemsList;
    delete propertyWidgetManager;
    delete flowData;
    delete loadStore;

    delete nodeScene;
    delete windowManager;
    delete flow_ui;
}
void FlowWidget::updateUI()
{
    nodeScene->update();
}
void FlowWidget::open(FileSystem* _fileSystem, QJsonObject &jsonObject)
{
    delete fileSystem;//replace the filesystem object
    fileSystem = _fileSystem;
    DeserializationHandler handler(
    {
       .restoreContext = true,
       .restoreData = false,
       .exceptionOnError = true,
       .exceptionOnFatal = true,
   });

    try {
        loadStore->deserialize(jsonObject, handler);
    } catch (DeserialistationException e) {
        handler.printMessages(true);

    }

}
bool FlowWidget::save(bool saveAs)
{
    SerializationHandler handler(
    {
      .saveContext = true,
      .saveData = false,
      .saveTempData = false,
      .exceptionOnError = true,
      .exceptionOnFatal = true
    });
    QJsonObject* completeJson = loadStore->serialize(handler);
    if(handler.errorOccured())
    {
       handler.printMessages();
       return false;
    }
    fileSystem->saveFile(this,completeJson, saveAs);
    delete completeJson;
    return true;

}

void FlowWidget::undo()
{
    undoRedoManager->undo();
}

void FlowWidget::redo()
{
    undoRedoManager->redo();
}
