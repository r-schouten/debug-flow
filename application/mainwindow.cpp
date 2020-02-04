#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    createToolbar();
    m_ui->setupUi(this);
    //when a node in a scene is clicked its property's will been shown in the right tab bar, to give the nodes acces to the tab bar the selectionmanager have a propertyWidgetManager to open the property's on a node is selected
    propertyWidgetManager = new PropertyWidgetManager(m_ui->propertiesWidget,m_ui->rightTabWidget);
    SelectionManager::getInstance()->setPropertyWidgetManager(propertyWidgetManager);

    windowManager = new WindowManager(m_ui->mdiArea);

    nodeScene = new NodeScene(windowManager);
    m_ui->graphicsView->setScene(nodeScene);

    itemsList = new ItemList(m_ui->resourceList,nodeScene);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
    UiUpdatetimer->start(30);
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
void MainWindow::newFlow()
{

}
void MainWindow::openFlow()
{

}

void MainWindow::saveFlow()
{

}

void MainWindow::closeFlow()
{

}

void MainWindow::pauseFlow()
{

}

void MainWindow::resumeFlow()
{

}

void MainWindow::clearFlow()
{

}

void MainWindow::createToolbar()
{
    QMenu *fileMenu = menuBar()->addMenu("file");
    QMenu *flowMenu = menuBar()->addMenu("flow");
    QToolBar *fileToolBar = addToolBar("load save");


    //new flow action
    const QIcon newIcon = QIcon::fromTheme("new", style()->standardIcon(QStyle::SP_FileIcon));
    newAction = new QAction(newIcon,"new", this);
    newAction->setShortcuts(QKeySequence::New);
    fileToolBar->addAction(newAction);
    fileMenu->addAction(newAction);

    //open flow action
    const QIcon openIcon = QIcon::fromTheme("open", style()->standardIcon(QStyle::SP_DialogOpenButton));
    openAction = new QAction(openIcon,"open", this);
    openAction->setShortcuts(QKeySequence::Open);
    fileToolBar->addAction(openAction);
    fileMenu->addAction(openAction);

    //save flow action
    const QIcon saveIcon = QIcon::fromTheme("save", style()->standardIcon(QStyle::SP_DialogSaveButton));
    saveAction = new QAction(saveIcon,"save", this);
    saveAction->setShortcuts(QKeySequence::Save);
    fileToolBar->addAction(saveAction);
    fileMenu->addAction(saveAction);

    fileToolBar->addSeparator();

    //pause flow action
    const QIcon pauseIcon = QIcon::fromTheme("pause flow", style()->standardIcon(QStyle::SP_MediaPause));
    pauseAction = new QAction(pauseIcon,"pause flow", this);
    fileToolBar->addAction(pauseAction);
    flowMenu->addAction(pauseAction);

    //pause flow action
    const QIcon resumeIcon = QIcon::fromTheme("resume flow", style()->standardIcon(QStyle::SP_MediaPlay));
    resumeAction = new QAction(resumeIcon,"resume flow", this);
    fileToolBar->addAction(resumeAction);
    flowMenu->addAction(resumeAction);

    //reset flow action
    const QIcon resetIcon = QIcon::fromTheme("reset flow", style()->standardIcon(QStyle::SP_DialogResetButton));
    resetAction = new QAction(resetIcon,"reset flow", this);
    fileToolBar->addAction(resetAction);
    flowMenu->addAction(resetAction);

    fileToolBar->setMovable(false);

}
