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
#include "windowmanager.h"
#include "graphicsview.h"
#include "globalconfig.h"
#include "nodescene.h"
#include "selectionmanager.h"

class Ui_flowWidget
{
public:
    QVBoxLayout *verticalLayout = nullptr;
    QSplitter *splitter = nullptr;
    GraphicsView *graphicsView = nullptr;
    QMdiArea *mdiArea = nullptr;
    QToolBar *mainToolBar = nullptr;
    QTreeWidget *resourceList = nullptr;
    QSplitter *sceneSplitter = nullptr;
    QTabWidget* rightTabWidget = nullptr;
    QScrollArea* propertiesWidget = nullptr;
    QScrollArea* undoRedoWidget = nullptr;
    QWidget* secondTab = nullptr;

    void setupUi(QWidget* flowWidget, SelectionManager* selectionManager)
    {

        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(flowWidget->sizePolicy().hasHeightForWidth());
        flowWidget->setSizePolicy(sizePolicy1);


        //layout and splitter
        verticalLayout = new QVBoxLayout(flowWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");

        splitter = new QSplitter(flowWidget);
        splitter->setObjectName("splitter");
        splitter->setEnabled(true);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Vertical);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(5);


        sceneSplitter = new QSplitter(splitter);
        sceneSplitter->setObjectName("sceneSplitter");
        sceneSplitter->setEnabled(true);

        sizePolicy1.setHeightForWidth(sceneSplitter->sizePolicy().hasHeightForWidth());
        sceneSplitter->setSizePolicy(sizePolicy1);
        sceneSplitter->setOrientation(Qt::Horizontal);
        sceneSplitter->setOpaqueResize(true);
        sceneSplitter->setHandleWidth(3);

        //resourcelist
        resourceList = new QTreeWidget(sceneSplitter);
        resourceList->setObjectName("treeWidget");
        resourceList->setMinimumSize(QSize(125,100));

        //nodescene
        graphicsView = new GraphicsView(sceneSplitter, selectionManager);
        graphicsView->setObjectName("nodesScene");
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(0, 200));

        sceneSplitter->addWidget(graphicsView);
        //right tab widget
        rightTabWidget = new QTabWidget(sceneSplitter);
        rightTabWidget->setSizePolicy(sizePolicy1);
        rightTabWidget->setObjectName("rightTabWidget");
        rightTabWidget->setMinimumSize(QSize(125,100));

        //properties tab in right tab widget
        propertiesWidget = new QScrollArea(rightTabWidget);
        propertiesWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        propertiesWidget->setObjectName("propertiesWidget");
        propertiesWidget->setSizePolicy(sizePolicy1);
        rightTabWidget->addTab(propertiesWidget,"node properties");

        //properties tab in right tab widget
        undoRedoWidget = new QScrollArea(rightTabWidget);
        undoRedoWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        undoRedoWidget->setObjectName("undo redo Widget");
        undoRedoWidget->setSizePolicy(sizePolicy1);
        rightTabWidget->addTab(undoRedoWidget,"undo redo");

        //new tab, for testing
        secondTab = new QWidget(rightTabWidget);
        secondTab->setObjectName("propertiesWidget");
        secondTab->setSizePolicy(sizePolicy1);
        rightTabWidget->addTab(secondTab,"second tab");

        sceneSplitter->setCollapsible(0,false);
        sceneSplitter->setCollapsible(1,false);
        sceneSplitter->setCollapsible(2,false);
        sceneSplitter->setSizes(QList<int>({100, 400, 50}));

        splitter->addWidget(sceneSplitter);

        //mdi area
        mdiArea = new QMdiArea(splitter);
        mdiArea->setObjectName("mdiArea");
        mdiArea->setDocumentMode(false);
        splitter->addWidget(mdiArea);

        verticalLayout->addWidget(splitter);


    }

};

