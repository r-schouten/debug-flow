#include "flowwidget.h"

FlowWidget::FlowWidget(QWidget *parent, FileSystem* _fileSystem) : QWidget(parent)
{
    flow_ui = new Ui_flowWidget();
    flow_ui->setupUi(this);

    dbgLogger = new DbgLogger();

    propertyWidgetManager = new PropertyWidgetManager(flow_ui->propertiesWidget,flow_ui->rightTabWidget, flow_ui->nodeViewerWidget, dbgLogger);
    selectionManager = new SelectionManager(propertyWidgetManager, dbgLogger);    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    windowManager = new WindowManager(flow_ui->mdiArea);
    undoRedoManager = new UndoRedoManager(flow_ui->undoRedoWidget);

    historicalUpdateManager = new HistoricalUpdateManager(dbgLogger);
    updateManager = new UpdateManager(dbgLogger);

    flowObjects = new FlowObjects(selectionManager, undoRedoManager, dbgLogger, windowManager, historicalUpdateManager, updateManager);

    flow_ui->nodeViewerWidget->setFlowObjects(flowObjects);
    nodeScene = new NodeScene(flowObjects);
    flow_ui->graphicsView->setData(flowObjects, nodeScene);

    loadStore = new LoadStore(flowObjects, nodeScene);

    undoRedoManager->setData(flowObjects, loadStore);

    if(_fileSystem == nullptr)
    {
        fileSystem = new FileSystem();
    }
    else
    {
        //used to open a file
        fileSystem = _fileSystem;
    }

    itemsList = new ItemList(flow_ui->resourceList,flowObjects, nodeScene);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &FlowWidget::updateUI);
    UiUpdatetimer->start(30);

    flow_ui->graphicsView->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);

    connect(undoRedoManager, SIGNAL(anythingChanged()), this, SLOT(anythingChanged()));
}


FlowWidget::~FlowWidget()
{
    delete UiUpdatetimer;

    delete itemsList;
    delete propertyWidgetManager;
    delete flowObjects;
    delete loadStore;

    delete nodeScene;
    delete windowManager;
    delete flow_ui;
    delete fileSystem;
    delete dbgLogger;
}
void FlowWidget::updateUI()
{
    nodeScene->update();
}
QString FlowWidget::getFileName()
{
    if(fileSystem->hasFileLocation)
    {
        return fileSystem->getFileName();
    }
    else
    {
        return "";
    }
}
void FlowWidget::anythingChanged()
{
    if(changesSaved)
    {
        changesSaved = false;
        emit setTabName(this, "*"+getFileName());
    }
}
bool FlowWidget::getchangesSaved()
{
    return changesSaved;
}
void FlowWidget::open(QJsonObject &jsonObject)
{
    DeserializationHandler handler(
    {
       .restoreContext = true,
       .restoreData = false,
       .exceptionOnError = true,
       .exceptionOnFatal = true,
   }, dbgLogger);

    try {
        loadStore->deserialize(jsonObject, handler);
    } catch (DeserialistationException e) {
        handler.printMessages(true);

    }
    changesSaved = true;
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
    },dbgLogger);
    QJsonObject* completeJson = loadStore->serialize(handler);
    if(handler.errorOccured())
    {
       handler.printMessages();
       return false;
    }
    bool succes = fileSystem->saveFile(this,completeJson, saveAs);
    delete completeJson;

    if(succes)
    {
        changesSaved = true;
        emit setTabName(this,getFileName());
    }
    return succes;
}

void FlowWidget::undo()
{
    undoRedoManager->undo();
}

void FlowWidget::redo()
{
    undoRedoManager->redo();
}
