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

    tagFilter->filterData(&result, bufferReader);

    //qDebug("result: %s",destination.toStdString().c_str());
    //qDebug() << result;
    console->moveCursor(QTextCursor::End);
    console->insertPlainText(result);
    console->moveCursor(QTextCursor::End);

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
