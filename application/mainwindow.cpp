#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
     m_ui->setupUi(this);
     connect(m_ui->saveAction,&QAction::triggered,this,&saveFlow);
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

    QJsonDocument doc(*serializedFlow);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    qDebug(strJson.toStdString().c_str());


    delete activeFlow;
    activeFlow = nullptr;
    newFlow();
    activeFlow->open(serializedFlow);

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

