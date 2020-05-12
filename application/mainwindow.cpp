#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
     m_ui->setupUi(this);
     connect(m_ui->newAction,&QAction::triggered,this,&newFlow);
     connect(m_ui->openAction,&QAction::triggered,this,&open);
     connect(m_ui->saveAction,&QAction::triggered,this,&save);
     connect(m_ui->saveAsAction,&QAction::triggered,this,&saveAs);

     connect(m_ui->undoAction,&QAction::triggered,this,&undo);
     connect(m_ui->redoAction,&QAction::triggered,this,&redo);

     newFlow();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


void MainWindow::makeFlow()
{
    FlowWidget* flowWidget = new FlowWidget();
    activeFlow = flowWidget;
    setCentralWidget(flowWidget);
}
void MainWindow::newFlow()
{
    if(activeFlow)delete activeFlow;

    makeFlow();
}
void MainWindow::open()
{
    if(!activeFlow)return;
    qDebug("[debug][MainWindow] openFlow()");

    FileSystem* fileSystem = new FileSystem;
    QJsonObject jsonObject;
    if(fileSystem->openFile(this, jsonObject))
    {
        if(activeFlow)delete activeFlow;
        makeFlow();
        activeFlow->open(fileSystem, jsonObject);
    }

}

void MainWindow::save()
{
    if(!activeFlow)return;
    qDebug("[debug][MainWindow] saveFlow()");
    activeFlow->save(false);

    //Utils::printJson(serializedFlow);

    //delete activeFlow;
    //activeFlow = nullptr;

    //makeFlow();
    //activeFlow->open(*serializedFlow);
}

void MainWindow::saveAs()
{
    if(!activeFlow)return;
    qDebug("[debug][MainWindow] saveFlow()");
    activeFlow->save(true);

}
void MainWindow::closeFlow()
{
    if(activeFlow)
    {

        delete activeFlow;
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
    activeFlow->undo();
}

void MainWindow::redo()
{
    activeFlow->redo();
}

