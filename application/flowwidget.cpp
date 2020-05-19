#include "flowwidget.h"

FlowWidget::FlowWidget(QWidget *parent) : QWidget(parent)
{
    selectionManager = new SelectionManager();

    flow_ui = new Ui_flowWidget();
    flow_ui->setupUi(this, selectionManager);


    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    propertyWidgetManager = new PropertyWidgetManager(flow_ui->propertiesWidget,flow_ui->rightTabWidget);
    selectionManager->setPropertyWidgetManager(propertyWidgetManager);

    windowManager = new WindowManager(flow_ui->mdiArea);

    undoRedoManager = new UndoRedoManager(flow_ui->undoRedoWidget);

    flowData = new FlowData(windowManager);

    flowObjects = new FlowObjects(selectionManager, undoRedoManager);

    nodeScene = new NodeScene(flowData, flowObjects);
    flow_ui->graphicsView->setScene(nodeScene);

    loadStore = new LoadStore(flowData, flowObjects, nodeScene);

    undoRedoManager->setData(flowData, loadStore);

    fileSystem = new FileSystem();

    itemsList = new ItemList(flow_ui->resourceList,flowObjects, nodeScene);

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
    delete fileSystem;
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
