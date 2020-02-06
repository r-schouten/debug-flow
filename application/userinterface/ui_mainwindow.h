#pragma once

#include <QListWidget>
#include <QTreeWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QAction>
#include <QMenuBar>

#include "windowmanager.h"
#include "graphicsview.h"
#include "globalconfig.h"
#include "nodescene.h"
class QMenuBar;

QT_BEGIN_NAMESPACE
class Ui_MainWindow
{
public:
    QWidget *centralWidget = nullptr;
    QVBoxLayout *verticalLayout = nullptr;
    QSplitter *splitter = nullptr;
    GraphicsView *graphicsView = nullptr;
    QMdiArea *mdiArea = nullptr;
    QToolBar *mainToolBar = nullptr;
    QTreeWidget *resourceList = nullptr;
    QSplitter *sceneSplitter = nullptr;
    QTabWidget* rightTabWidget = nullptr;
    QScrollArea* propertiesWidget = nullptr;
    QWidget* secondTab = nullptr;

    QMenu *windowMenu = nullptr;
    QAction *newAction = nullptr;
    QAction *openAction = nullptr;
    QAction *saveAction = nullptr;
    QAction *pauseAction = nullptr;
    QAction *resetAction = nullptr;
    QAction *resumeAction = nullptr;
    void setupUi(QMainWindow *MainWindow)
    {
        //mainwindow
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(PROGRAM_NAME);

        MainWindow->resize(1200, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);


//        //central widget
//        centralWidget = new QWidget(MainWindow);
//        centralWidget->setObjectName("centralWidget");
//        centralWidget->setEnabled(true);
//        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        sizePolicy1.setHorizontalStretch(0);
//        sizePolicy1.setVerticalStretch(0);
//        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
//        centralWidget->setSizePolicy(sizePolicy1);


//        //layout and splitter
//        verticalLayout = new QVBoxLayout(centralWidget);
//        verticalLayout->setSpacing(6);
//        verticalLayout->setContentsMargins(11, 11, 11, 11);
//        verticalLayout->setObjectName("verticalLayout");

//        splitter = new QSplitter(centralWidget);
//        splitter->setObjectName("splitter");
//        splitter->setEnabled(true);
//        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
//        splitter->setSizePolicy(sizePolicy1);
//        splitter->setOrientation(Qt::Vertical);
//        splitter->setOpaqueResize(true);
//        splitter->setHandleWidth(5);


//        sceneSplitter = new QSplitter(splitter);
//        sceneSplitter->setObjectName("sceneSplitter");
//        sceneSplitter->setEnabled(true);

//        sizePolicy1.setHeightForWidth(sceneSplitter->sizePolicy().hasHeightForWidth());
//        sceneSplitter->setSizePolicy(sizePolicy1);
//        sceneSplitter->setOrientation(Qt::Horizontal);
//        sceneSplitter->setOpaqueResize(true);
//        sceneSplitter->setHandleWidth(3);

//        //resourcelist
//        resourceList = new QTreeWidget(sceneSplitter);
//        resourceList->setObjectName("treeWidget");
//        resourceList->setMinimumSize(QSize(125,100));

//        //nodescene
//        graphicsView = new GraphicsView(sceneSplitter);
//        graphicsView->setObjectName("nodesScene");
//        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
//        graphicsView->setSizePolicy(sizePolicy1);
//        graphicsView->setMinimumSize(QSize(0, 200));

//        sceneSplitter->addWidget(graphicsView);
//        //right tab widget
//        rightTabWidget = new QTabWidget(sceneSplitter);
//        rightTabWidget->setSizePolicy(sizePolicy1);
//        rightTabWidget->setObjectName("rightTabWidget");
//        rightTabWidget->setMinimumSize(QSize(125,100));

//        //properties tab in right tab widget
//        propertiesWidget = new QScrollArea(rightTabWidget);
//        propertiesWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        propertiesWidget->setObjectName("propertiesWidget");
//        propertiesWidget->setSizePolicy(sizePolicy1);
//        rightTabWidget->addTab(propertiesWidget,"node properties");

//        //new tab, for testing
//        secondTab = new QWidget(rightTabWidget);
//        secondTab->setObjectName("propertiesWidget");
//        secondTab->setSizePolicy(sizePolicy1);
//        rightTabWidget->addTab(secondTab,"second tab");

//        sceneSplitter->setCollapsible(0,false);
//        sceneSplitter->setCollapsible(1,false);
//        sceneSplitter->setCollapsible(2,false);
//        sceneSplitter->setSizes(QList<int>({100, 400, 50}));

//        splitter->addWidget(sceneSplitter);

//        //mdi area
//        mdiArea = new QMdiArea(splitter);
//        mdiArea->setObjectName("mdiArea");
//        mdiArea->setDocumentMode(false);
//        splitter->addWidget(mdiArea);

//        verticalLayout->addWidget(splitter);

        createToolbar(MainWindow);

        //MainWindow->setCentralWidget(centralWidget);
        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", PROGRAM_NAME, nullptr));
    }

    void createToolbar(QMainWindow *MainWindow)
    {
        QMenu *fileMenu = MainWindow->menuBar()->addMenu("file");
        QMenu *flowMenu = MainWindow->menuBar()->addMenu("flow");
        QToolBar *fileToolBar = MainWindow->addToolBar("load save");


        //new flow action
        const QIcon newIcon = QIcon::fromTheme("new", MainWindow->style()->standardIcon(QStyle::SP_FileIcon));
        newAction = new QAction(newIcon,"new", MainWindow);
        newAction->setShortcuts(QKeySequence::New);
        fileToolBar->addAction(newAction);
        fileMenu->addAction(newAction);

        //open flow action
        const QIcon openIcon = QIcon::fromTheme("open", MainWindow->style()->standardIcon(QStyle::SP_DialogOpenButton));
        openAction = new QAction(openIcon,"open", MainWindow);
        openAction->setShortcuts(QKeySequence::Open);
        fileToolBar->addAction(openAction);
        fileMenu->addAction(openAction);

        //save flow action
        const QIcon saveIcon = QIcon::fromTheme("save", MainWindow->style()->standardIcon(QStyle::SP_DialogSaveButton));
        saveAction = new QAction(saveIcon,"save", MainWindow);
        saveAction->setShortcuts(QKeySequence::Save);
        fileToolBar->addAction(saveAction);
        fileMenu->addAction(saveAction);

        fileToolBar->addSeparator();

        //pause flow action
        const QIcon pauseIcon = QIcon::fromTheme("pause flow", MainWindow->style()->standardIcon(QStyle::SP_MediaPause));
        pauseAction = new QAction(pauseIcon,"pause flow", MainWindow);
        fileToolBar->addAction(pauseAction);
        flowMenu->addAction(pauseAction);

        //pause flow action
        const QIcon resumeIcon = QIcon::fromTheme("resume flow", MainWindow->style()->standardIcon(QStyle::SP_MediaPlay));
        resumeAction = new QAction(resumeIcon,"resume flow", MainWindow);
        fileToolBar->addAction(resumeAction);
        flowMenu->addAction(resumeAction);

        //reset flow action
        const QIcon resetIcon = QIcon::fromTheme("reset flow", MainWindow->style()->standardIcon(QStyle::SP_DialogResetButton));
        resetAction = new QAction(resetIcon,"reset flow", MainWindow);
        fileToolBar->addAction(resetAction);
        flowMenu->addAction(resetAction);

        fileToolBar->setMovable(false);

    }
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}

QT_END_NAMESPACE

