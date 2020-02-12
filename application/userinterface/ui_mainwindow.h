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
    QAction *undoAction = nullptr;
    QAction *redoAction = nullptr;
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

        createToolbar(MainWindow);

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
        QMenu *editMenu = MainWindow->menuBar()->addMenu("edit");
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

        //menu only
        //undo action
        undoAction = new QAction("undo", MainWindow);
        editMenu->addAction(undoAction);
        undoAction->setShortcut(QKeySequence::Undo);

        //redo  action
        redoAction = new QAction("redo", MainWindow);
        editMenu->addAction(redoAction);
        redoAction->setShortcut(QKeySequence::Redo);

    }
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
}

QT_END_NAMESPACE

