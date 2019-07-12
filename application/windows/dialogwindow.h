#pragma once
#include <QDialog>

#include "windowbase.h"


class DialogWindow : public WindowBase, public QDialog
{
public:
    DialogWindow();
};

