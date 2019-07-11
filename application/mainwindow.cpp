#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_status(new QLabel),
    m_settings(new SettingsDialog)
{
    m_ui->setupUi(this);

    filteredConsole = dynamic_cast<FilteredConsole*>(m_ui->consoleWidget);
    if(!filteredConsole) qFatal("promote from qwidget to FilteredConsole failed");

    serialNode = new SerialNode(m_settings);
    filteredConsole->addSubscription(serialNode);


    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();


}

MainWindow::~MainWindow()
{
    delete m_settings;
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
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(m_ui->actionClear, &QAction::triggered, filteredConsole, &FilteredConsole::clear);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
