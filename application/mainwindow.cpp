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

     connect(m_ui->flowTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(tabClose(int)));
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
void MainWindow::changeTabName(QWidget* widget, QString tabName)
{
    int index = m_ui->flowTabWidget->indexOf(widget);
    m_ui->flowTabWidget->setTabText(index, tabName);
}

QEvent MainWindow::tabClose(int index)
{
    QEvent event(QEvent::Close);
    FlowWidget* flowToDelete = (FlowWidget*)m_ui->flowTabWidget->widget(index);
    if(flowToDelete == nullptr)
    {
        qFatal("[fatal][MainWindow] flowToDelete is nullptr");
    }

    if(flowToDelete->getchangesSaved() == false)
    {
        QMessageBox msgBox;
        QString messageFileName;
        if(flowToDelete->getFileName().isEmpty())
        {
            messageFileName = m_ui->flowTabWidget->tabText(index);
        }
        else
        {
            messageFileName = flowToDelete->getFileName();
        }
        msgBox.setWindowTitle("Save changes");
        msgBox.setText(QString("%1 is not saved").arg(messageFileName));
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
        {
            bool succes = flowToDelete->save(false);
            if(succes)
            {
                event.accept();
            }
            else
            {
                event.ignore();
                return event;
            }
            break;
        }
        case QMessageBox::Discard:
            event.accept();
            break;
        case QMessageBox::Cancel:
            event.ignore();
            return event;
            break;
        default:
            event.ignore();
            return event;
            break;
        }
    }
    delete flowToDelete;
    return event;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    while(m_ui->flowTabWidget->count() > 0)
    {
        QEvent tabCloseEvent = tabClose(0);
        if(tabCloseEvent.isAccepted() == false)
        {
            event->ignore();
            return;
        }
    }
}
FlowWidget* MainWindow::makeFlow(QString name)
{
    FlowWidget* newFlow = new FlowWidget();
    m_ui->flowTabWidget->addTab(newFlow, name);
    setCurrentFlow(newFlow);
    connect(newFlow, SIGNAL(setTabName(QWidget*, QString)), this, SLOT(changeTabName(QWidget*, QString)));
    return newFlow;
}
void MainWindow::newFlow()
{
    makeFlow("new flow");
}
void MainWindow::open()
{
    DbgLogger::getStaticLogger()->verbose("MainWindow",__FUNCTION__,"openFlow()");

    FileSystem* fileSystem = new FileSystem();
    QJsonObject jsonObject;
    QString fileName;
    if(fileSystem->openFile(this, jsonObject, fileName))
    {
        FlowWidget* newFlow = new FlowWidget(nullptr, fileSystem);
        m_ui->flowTabWidget->addTab(newFlow, fileName);
        setCurrentFlow(newFlow);
        connect(newFlow, SIGNAL(setTabName(QWidget*, QString)), this, SLOT(changeTabName(QWidget*, QString)));
        newFlow->open(jsonObject);
    }
}

void MainWindow::save()
{
    DbgLogger::getStaticLogger()->verbose("MainWindow",__FUNCTION__,"saveFlow()");
    if(anyFlowOpen())
    {
        getCurrentFlow()->save(false);
    }
}

void MainWindow::saveAs()
{
    DbgLogger::getStaticLogger()->verbose("MainWindow",__FUNCTION__,"saveFlow()");
    if(anyFlowOpen())
    {
        getCurrentFlow()->save(true);
    }

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

