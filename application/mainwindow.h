#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QAction>

#include "flowwidget.h"
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeTabName(QWidget *widget, QString tabName);
private slots:
    void newFlow();
    void open();
    void save();
    void saveAs();
    void closeFlow();
    void pauseFlow();
    void resumeFlow();
    void clearFlow();
    void undo();
    void redo();
    QEvent tabClose(int index);
private:
    Ui::MainWindow *m_ui = nullptr;

    FlowWidget *makeFlow(QString name);
    void setCurrentFlow(FlowWidget *flowWidget);
    FlowWidget *getCurrentFlow();
    bool anyFlowOpen();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
