#include "mainwindow.h"

#include <mdiwindow.cpp>

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
    //newSubWindow->setWidget(console);
    //m_ui->mdiArea->addSubWindow(newSubWindow);


    console->addSubscription(serialNode);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(true);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();

}

MainWindow::~MainWindow()
{
    delete m_ui;
}



void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}



void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, serialNode, &SerialNode::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, serialNode, &SerialNode::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, serialNode, &SerialNode::openSettings);
    connect(m_ui->actionClear, &QAction::triggered, filteredConsole, &FilteredConsole::clear);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
