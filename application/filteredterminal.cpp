#include "filteredterminal.h"
#include "ui_filteredterminal.h"

FilteredTerminal::FilteredTerminal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilteredTerminal)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    show();

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

FilteredTerminal::~FilteredTerminal()
{
    delete ui;
}

void FilteredTerminal::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("FilteredConsole::notifyBufferUpdate() : bufferReader == nullptr");
    }
    QString result;
    result.reserve(source->bufferReader->availableSize());

    QTextCharFormat oldFormat = currentCharFormat;
    bool styleChanged = tagFilter->filterData(&result, source->bufferReader, &currentCharFormat);

    //qDebug("result: %s",destination.toStdString().c_str());
    //qDebug() << result;
    console->moveCursor(QTextCursor::End);
    console->setCurrentCharFormat(oldFormat);
    console->insertPlainText(result);
    console->moveCursor(QTextCursor::End);

    if(styleChanged)
    {
        //when ansi is found the filter stops searching and is perhaps not empty, read it again
        NotifyBufferUpdate(source);
    }
}

void FilteredTerminal::keyPressEvent(QKeyEvent *e)
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

void FilteredTerminal::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    console->setFocus();
}

void FilteredTerminal::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void FilteredTerminal::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
void FilteredTerminal::clear()
{
    console->clear();
}
