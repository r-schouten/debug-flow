#include "simpleconsole.h"

SimpleConsole::SimpleConsole(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :NodeBase(updateManager,dbgLogger)
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
void SimpleConsole::doBufferUpdate(Subscription *source, int availableSize)
{
    console->setUpdatesEnabled(false);

    if(source->bufferReader == nullptr){
        qFatal("SimpleConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    bool styleChanged = true;
    while(styleChanged)
    {
        QString result;
       // result.reserve(source->bufferReader->availableSize());

        QTextCharFormat oldFormat = currentCharFormat;
        styleChanged = ansiReader->filterData(&result, source->bufferReader, &currentCharFormat);


        console->moveCursor(QTextCursor::End);
        console->setCurrentCharFormat(oldFormat);
        console->insertPlainText(result);
        console->moveCursor(QTextCursor::End);

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

std::string SimpleConsole::getNodeName()
{
    return CLASSNAME;

}

void SimpleConsole::reset()
{
console->clear();
}
void SimpleConsole::clear()
{
    console->clear();
}
