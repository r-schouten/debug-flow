#include "consolewidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent):
    QPlainTextEdit(parent)
{
    setReadOnly(true);

    //choose a console color
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);

    //make line number area
    lineNumberArea = new LineNumberArea(this);


    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

    updateLineNumberAreaWidth(0);
}

void ConsoleWidget::setMaxLines(int lines)
{
    maxBlockCount = lines;
}
void ConsoleWidget::append(QString textToAdd, QTextCharFormat format,TimeStamp_t* timeStamp, bool autoScroll)
{
    document()->setMaximumBlockCount(0);
    oldBlockCount = document()->blockCount();
    if(autoScroll)
    {
        moveCursor(QTextCursor::End);
        setCurrentCharFormat(format);
        insertPlainText(textToAdd);
        moveCursor(QTextCursor::End);
    }
    else {
        QTextCursor cursor = textCursor();

        cursor.movePosition(QTextCursor::End);
        cursor.setCharFormat(format);
        cursor.insertText(textToAdd);
    }
    //setMaximumBlockCount is a bit misused here,
    //when blocks are deleted at the end the QDocument class provides no way to find how much blocks that where.
    int blockCountBeforeDeletion = document()->blockCount();
    document()->setMaximumBlockCount(maxBlockCount);
    int blockCountAfter = document()->blockCount();

    deletedBlocks += blockCountBeforeDeletion - blockCountAfter;
    int insertedBlocks = blockCountBeforeDeletion-oldBlockCount;

    QTextBlock block = document()->findBlockByNumber(blockCountBeforeDeletion - insertedBlocks-1);
    for(int i = blockCountBeforeDeletion - insertedBlocks-1;i < blockCountAfter ;i++)
    {
        TextBlockWithTimestamp* userData = new TextBlockWithTimestamp();
        userData->blockNr = block.blockNumber()+1 + deletedBlocks;
        userData->timestamp.setTimestamp(timeStamp->getTimestamp());
        block.setUserData(userData);
        block = block.next();
    }
}

//------functions for the line number widget
int ConsoleWidget::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount()+deletedBlocks);
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * (digits + 9+2);

    return space;
}
void ConsoleWidget::updateLineNumberAreaWidth(int newBlockCount)
{
    int areaWidth = lineNumberAreaWidth();
    if(oldAreaWidth != areaWidth)
    {
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
        oldAreaWidth = areaWidth;
    }
}

void ConsoleWidget::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ConsoleWidget::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void ConsoleWidget::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    char buffer[32];
    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString blockText = block.text();
            QString text;
            TextBlockWithTimestamp* userData = dynamic_cast<TextBlockWithTimestamp*>(block.userData());
            if(userData)
            {
                text = QString::number(userData->blockNr);
                text += " - " + userData->timestamp.toHourMinuteSecond(buffer, sizeof(buffer));
            }
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, text);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
