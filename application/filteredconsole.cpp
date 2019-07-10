#include "filteredconsole.h"

FilteredConsole::FilteredConsole(QWidget *parent)
{
    console = new QPlainTextEdit(this);
    console->setReadOnly(true);
    console->document()->setMaximumBlockCount(1000);

    QComboBox *combobox = new QComboBox(this);
    QComboBox *combobox2 = new QComboBox(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *verticalLayout = new QHBoxLayout(this);
    verticalLayout->addWidget(combobox);
    verticalLayout->addWidget(combobox2);

    layout->addLayout(verticalLayout);
    layout->addWidget(console);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    console->setPalette(p);

    tagFilter = new TagFilter();
}

void FilteredConsole::notifyBufferUpdate()
{
    if(bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(bufferReader->availableSize());

    ANSICode ansiCode = tagFilter->filterData(&result, bufferReader);

    //qDebug("result: %s",destination.toStdString().c_str());
    //qDebug() << result;
    console->moveCursor(QTextCursor::End);
    console->setCurrentCharFormat(currentCharFormat);
    console->insertPlainText(result);
    console->moveCursor(QTextCursor::End);

    if(ansiCode.type != ANSIType::NONE)
    {
        applyANSICode(ansiCode);
        //when ansi is found the filter stops searching and is perhaps not empty, read it again
        notifyBufferUpdate();
    }
}
void FilteredConsole::applyANSICode(ANSICode& ansiCode)
{
    if(ansiCode.type == ANSIType::FORMATTING)
    {
        if(ansiCode.value == 0)
        {
            QTextCharFormat format;
            currentCharFormat = format;
        }
        else if((ansiCode.value >= 30) && (ansiCode.value <= 37))
        {
            QList<QColor> ansiColors;
            ansiColors << Qt::black << Qt::red << Qt::green << Qt::yellow << Qt::blue << Qt::magenta << Qt::cyan << Qt::white;

            currentCharFormat.setForeground(ansiColors[ansiCode.value-30]);
        }
    }
    else if(ansiCode.type == ANSIType::ERROR)
    {
        console->moveCursor(QTextCursor::End);
        console->insertPlainText("{ansi error}");
    }
}
void FilteredConsole::keyPressEvent(QKeyEvent *e)
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

void FilteredConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    console->setFocus();
}

void FilteredConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void FilteredConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
void FilteredConsole::clear()
{
    console->clear();
}
