#include "simpleconsole.h"

SimpleConsole::SimpleConsole(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger)
{
    console = new QPlainTextEdit(this);
    console->setReadOnly(true);
    console->document()->setMaximumBlockCount(1000);

    layout = new QVBoxLayout(this);

    layout->addWidget(console);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    console->setPalette(p);

    ansiReader = new AnsiEscapeReader();
}

SimpleConsole::~SimpleConsole()
{
    delete ansiReader;
}

NodeSettingsBase *SimpleConsole::getNodeSettings()
{
    return nullptr;//todo make settings
}
void SimpleConsole::NotifyBufferUpdate(Subscription *source)
{
    console->setUpdatesEnabled(false);

    if(source->bufferReader == nullptr){
        qFatal("SimpleConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = ansiReader->filterData(&result, source->bufferReader, &currentCharFormat);


    console->moveCursor(QTextCursor::End);
    console->setCurrentCharFormat(oldFormat);
    console->insertPlainText(result);
    console->moveCursor(QTextCursor::End);

    if(styleChanged)
    {
        //when ansi is found the filter stops searching and is perhaps not empty, read it again
        NotifyBufferUpdate(source);
    }
    console->setUpdatesEnabled(true);

}

void SimpleConsole::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Backspace:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            break;
        }
}

void SimpleConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    console->setFocus();
}

void SimpleConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void SimpleConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
void SimpleConsole::clear()
{
    console->clear();
}
