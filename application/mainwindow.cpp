#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
     m_ui->setupUi(this);
     setCentralWidget(m_ui->flowTabWidget);
     connect(m_ui->newAction,SIGNAL(triggered()),this,SLOT(newFlow()));
     connect(m_ui->openAction,SIGNAL(triggered()),this,SLOT(open()));
     connect(m_ui->saveAction,SIGNAL(triggered()),this,SLOT(save()));
     connect(m_ui->saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

     connect(m_ui->undoAction,SIGNAL(triggered()),this,SLOT(undo()));
     connect(m_ui->redoAction,SIGNAL(triggered()),this,SLOT(redo()));


     newFlow();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::setCurrentFlow(FlowWidget* flowWidget)
{
    m_ui->flowTabWidget->setCurrentWidget(flowWidget);
}
FlowWidget* MainWindow::getCurrentFlow()
{
    return (FlowWidget*)m_ui->flowTabWidget->currentWidget();
}
bool MainWindow::anyFlowOpen()
{
    return (m_ui->flowTabWidget->count() !=0);
}
FlowWidget* MainWindow::makeFlow(QString name)
{
    FlowWidget* flowWidget = new FlowWidget();
    m_ui->flowTabWidget->addTab(flowWidget, name);
    setCurrentFlow(flowWidget);
    return flowWidget;
}
void MainWindow::newFlow()
{
    makeFlow("new flow");
}
void MainWindow::open()
{
    qDebug("[debug][MainWindow] openFlow()");

    FileSystem* fileSystem = new FileSystem;
    QJsonObject jsonObject;
    QString fileName;
    if(fileSystem->openFile(this, jsonObject, fileName))
    {
        FlowWidget* newFlow = makeFlow(fileName);
        newFlow->open(fileSystem, jsonObject);//hand the ownership of filesystem over to the flow
    }
}

void MainWindow::save()
{
    qDebug("[debug][MainWindow] saveFlow()");
    if(anyFlowOpen())
    {
        getCurrentFlow()->save(false);
    }

    //Utils::printJson(serializedFlow);

    //delete activeFlow;
    //activeFlow = nullptr;

    //makeFlow();
    //activeFlow->open(*serializedFlow);
}

void MainWindow::saveAs()
{
    qDebug("[debug][MainWindow] saveFlow()");
    if(anyFlowOpen())
    {
        getCurrentFlow()->save(true);
    }

}
void MainWindow::closeFlow()
{
    if(anyFlowOpen())
    {
        delete getCurrentFlow();
    }
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

void MainWindow::undo()
{
    if(anyFlowOpen())
    {
        getCurrentFlow()->undo();
    }
}

void MainWindow::redo()
{
    if(anyFlowOpen())
    {
        getCurrentFlow()->redo();
    }
}

