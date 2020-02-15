#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
     m_ui->setupUi(this);
     connect(m_ui->saveAction,&QAction::triggered,this,&saveFlow);
     connect(m_ui->undoAction,&QAction::triggered,this,&undo);
     connect(m_ui->redoAction,&QAction::triggered,this,&redo);

     newFlow();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::newFlow()
{
    FlowWidget* flowWidget = new FlowWidget();
    activeFlow = flowWidget;
    setCentralWidget(flowWidget);
}
void MainWindow::openFlow()
{

}

void MainWindow::saveFlow()
{
    if(!activeFlow)return;
    qDebug("[debug][MainWindow] saveFlow()");
    QJsonObject* serializedFlow = activeFlow->save();

    //Utils::printJson(serializedFlow);

    delete activeFlow;
    activeFlow = nullptr;

    newFlow();
    activeFlow->open(*serializedFlow);

    delete serializedFlow;
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

void MainWindow::undo()
{
    activeFlow->undo();
}

void MainWindow::redo()
{
    activeFlow->redo();
}

