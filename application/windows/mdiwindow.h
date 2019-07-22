#pragma once

#include "windowbase.h"

#include <QMdiSubWindow>
#include <qmdiarea.h>


class MdiWindow : public WindowBase, public QMdiSubWindow
{
public:
    MdiWindow(QMdiArea* mdiArea)
    {
        //mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation);
        //mdiArea->addSubWindow(this);
    }
};

