#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    propertyWidgetManager = new PropertyWidgetManager(m_ui->propertiesWidget,m_ui->rightTabWidget);
    SelectionManager::getInstance()->setPropertyWidgetManager(propertyWidgetManager);

    windowManager = new WindowManager(m_ui->mdiArea);

    nodeScene = new NodeScene(windowManager);
    m_ui->graphicsView->setScene(nodeScene);

    itemsList = new ItemList(m_ui->resourceList,nodeScene);

//    UiUpdatetimer = new QTimer(this);
//    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
//    UiUpdatetimer->start(30);
    m_ui->graphicsView->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete UiUpdatetimer;
}
void MainWindow::updateUI()
{
    nodeScene->update();
}

