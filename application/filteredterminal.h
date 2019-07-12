#pragma once

#include "tagfilter.h"

#include <QDialog>
#include <QTextCharFormat>
#include <inputnode.h>
#include <qplaintextedit.h>

namespace Ui {
class FilteredTerminal;
}

class FilteredTerminal : public QDialog , public InputNode
{
    Q_OBJECT

public:
    explicit FilteredTerminal(QWidget *parent = nullptr);
    ~FilteredTerminal();
    void clear();
    void NotifyBufferUpdate(Subscription *source)override;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QTextCharFormat currentCharFormat;
    QPlainTextEdit* console = nullptr;
    TagFilter *tagFilter = nullptr;
    Ui::FilteredTerminal *ui;
};

