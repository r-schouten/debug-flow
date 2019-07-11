#pragma once

#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QTextDocument>

#include "outputnode.h"
#include "tagfilter.h"
class FilteredConsole : public QWidget , public OutputNode
{
public:
    explicit FilteredConsole(QWidget *parent = nullptr);
    void clear();
    void notifyBufferUpdate()override;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QTextCharFormat currentCharFormat;
    QPlainTextEdit* console = nullptr;
    TagFilter *tagFilter = nullptr;
};

