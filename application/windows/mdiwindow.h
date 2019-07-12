#pragma once

#include "windowbase.h"

#include <QMdiSubWindow>
#include <qmdiarea.h>


class MdiWindow : public WindowBase
{
public:
    MdiWindow(QMdiArea* mdiArea)
    {
        mdiArea->addSubWindow(this);
    }
};

