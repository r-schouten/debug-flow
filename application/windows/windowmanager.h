#pragma once
#include "dialogwindow.h"
#include "mdiwindow.h"

#include <QMdiArea>

class WindowManager
{
public:
    WindowManager(QMdiArea *mdiArea);

    QWidget *getMdiWindow();
    DialogWindow *getDialogWindow();
    MdiWindow *getMdiWindow(QWidget *widget);
    void deleteMdiWindow(QWidget *window);
private:
    QMdiArea* mdiArea = nullptr;
};
