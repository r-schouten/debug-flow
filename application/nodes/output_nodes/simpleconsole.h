#pragma once


#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QScrollBar>
#include "ansiescapereader.h"

#include "outputnode.h"


class SimpleConsole : public QWidget, public InputNode
{

public:
    void clear();
    void NotifyBufferUpdate(Subscription *source)override;

    SimpleConsole(DbgLogger *dbgLogger);
    virtual ~SimpleConsole();
    NodeSettingsBase *getNodeSettings();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QVBoxLayout *layout = nullptr;

    QTextCharFormat currentCharFormat;
    QPlainTextEdit* console = nullptr;
    AnsiEscapeReader *ansiReader = nullptr;

    // NodeBase interface
public:
    std::string getNodeName();
    void reset();
};
