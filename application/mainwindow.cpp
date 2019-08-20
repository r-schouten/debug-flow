#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);


    windowManager = new WindowManager(m_ui->mdiArea);

    nodeScene = new NodeScene(windowManager);
    m_ui->nodesScene->setScene(nodeScene);

    sceneComponents = new SceneComponents(m_ui->resourceList, nodeScene, m_ui->rightTabWidget, m_ui->propertiesWidget);

    itemsList = new ItemList(sceneComponents);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
    UiUpdatetimer->start(30);
    m_ui->nodesScene->setSceneRect(0, 0, graphicsViewWidth, graphicsViewHeight);
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

