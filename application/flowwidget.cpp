#include "flowwidget.h"

FlowWidget::FlowWidget(QWidget *parent) : QWidget(parent)
{
    m_ui = new Ui_flowWidget();
    m_ui->setupUi(this);
    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    propertyWidgetManager = new PropertyWidgetManager(m_ui->propertiesWidget,m_ui->rightTabWidget);
    SelectionManager::getInstance()->setPropertyWidgetManager(propertyWidgetManager);

    windowManager = new WindowManager(m_ui->mdiArea);

    flowData = new FlowData(windowManager);

    nodeScene = new NodeScene(flowData);

    loadStore = new LoadStore(flowData, nodeScene);

    m_ui->graphicsView->setScene(nodeScene);

    itemsList = new ItemList(m_ui->resourceList,nodeScene);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &FlowWidget::updateUI);
    UiUpdatetimer->start(30);
    m_ui->graphicsView->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);
}
FlowWidget::~FlowWidget()
{
    delete UiUpdatetimer;
    delete m_ui;
    delete nodeScene;
    delete itemsList;
    delete windowManager;
    delete propertyWidgetManager;
    delete flowData;
    delete loadStore;
}
void FlowWidget::updateUI()
{
    nodeScene->update();
}
void FlowWidget::open(QJsonObject &jsonObject)
{
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


//    if(handler.errorOccured())
//    {
//        handler.printMessages(true);
//    }
}
QJsonObject* FlowWidget::save()
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
   }
   return completeJson;
}
