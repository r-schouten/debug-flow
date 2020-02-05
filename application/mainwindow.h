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

private slots:
    void newFlow();
    void openFlow();
    void saveFlow();
    void closeFlow();
    void pauseFlow();
    void resumeFlow();
    void clearFlow();
private:
    Ui::MainWindow *m_ui = nullptr;
    FlowWidget* activeFlow = nullptr;

};
