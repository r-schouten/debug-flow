#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel)
{
    //terminal = new FilteredTerminal();
    m_ui->setupUi(this);

    //if(!terminal) qFatal("promote from qwidget to FilteredConsole failed");
    serialNode = new SerialNode();
    //terminal->addSubscription(serialNode);
    m_ui->mdiArea->setViewMode(QMdiArea::TabbedView);

    WindowBase* window = new MdiWindow(m_ui->mdiArea);
    FilteredConsole* console = new FilteredConsole(window);
    console->addSubscription(serialNode);

    WindowBase* window2 = new MdiWindow(m_ui->mdiArea);
    FilteredConsole* console2 = new FilteredConsole(window2);
    console2->addSubscription(serialNode);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(true);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();

    nodeScene = new NodeScene();
    m_ui->nodesScene->setScene(nodeScene);

    VisualSerialNode *node = new VisualSerialNode();
    nodeScene->addItem(node);

    UiUpdatetimer = new QTimer(this);
    connect(UiUpdatetimer, &QTimer::timeout, this, &MainWindow::updateUI);
    UiUpdatetimer->start(30);
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete UiUpdatetimer;
}
void MainWindow::updateUI()
{
    //m_ui->nodesScene->fitInView(0, 0, 1000, 300, Qt::KeepAspectRatio);
    m_ui->nodesScene->setSceneRect(0, 0, 1000, 300);
    nodeScene->update();
}


void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, serialNode, &SerialNode::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, serialNode, &SerialNode::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, serialNode, &SerialNode::openSettings);
    connect(m_ui->actionClear, &QAction::triggered, filteredConsole, &FilteredConsole::clear);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
