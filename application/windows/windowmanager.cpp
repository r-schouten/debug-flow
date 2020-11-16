#include "windowmanager.h"
WindowManager::WindowManager(QMdiArea* mdiArea)
    :mdiArea(mdiArea)
{
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation);
}
MdiWindow* WindowManager::getMdiWindow(QWidget* widget)
{
    MdiWindow* window = new MdiWindow(mdiArea);
    window->setWidget(widget);

    mdiArea->addSubWindow(window);
    window->show();
    return window;
}
DialogWindow* WindowManager::getDialogWindow()
{
    return new DialogWindow();
}
void WindowManager::removeMdiWindow(QWidget* window)
{
    mdiArea->removeSubWindow(window);
}
