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
void ConsoleWidget::clear()
{
    QPlainTextEdit::clear();
    deletedBlocks = 0;
}
void ConsoleWidget::setMaxLines(int lines)
{
    maxBlockCount = lines;
}
void ConsoleWidget::setLineNumbersEnabled(bool enabled)
{
    lineNumbersEnabled = enabled;
    oldAreaWidth = 0;

    sideLineEnabled = lineNumbersEnabled | timeEnabled;
}
void ConsoleWidget::setTimeEnabled(bool enabled)
{
    timeEnabled = enabled;
    sideLineEnabled = lineNumbersEnabled | timeEnabled;

}
void ConsoleWidget::append(QString textToAdd, QTextCharFormat format,MetaData_t* metaData, bool autoScroll)
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
        if(!block.userData())
        {
            TextBlockWithMetaData* userData = new TextBlockWithMetaData();
            userData->blockNr = block.blockNumber()+1 + deletedBlocks;
            userData->metaData.setTimestamp(metaData->getTimestamp());
            block.setUserData(userData);
        }
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
    int space = 3;
    if(lineNumbersEnabled) space+= fontMetrics().horizontalAdvance(QLatin1Char('9')) * (digits);
    if(timeEnabled) space+=40;
    if(lineNumbersEnabled&timeEnabled) space+=5;
    return space;
}
void ConsoleWidget::updateLineNumberAreaWidth(int newBlockCount)
{
    if(sideLineEnabled)
    {
        int areaWidth = lineNumberAreaWidth();
        if(oldAreaWidth != areaWidth)
        {
            setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
            oldAreaWidth = areaWidth;
        }
    }
    else
    {
        setViewportMargins(0, 0, 0, 0);
    }
}

void ConsoleWidget::updateLineNumberArea(const QRect &rect, int dy)
{
    if(!sideLineEnabled)return;
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

    if(!sideLineEnabled)return;
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void ConsoleWidget::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    if(!sideLineEnabled)return;
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible()&&( bottom >= event->rect().top()))
        {
            if(block.next().isValid() == false)
            {
                if(block.length() == 0)
                {
                    break;
                }
            }
            QString blockText = block.text();
            QString text;
            TextBlockWithMetaData* userData = dynamic_cast<TextBlockWithMetaData*>(block.userData());
            if(userData)
            {
                if(timeEnabled)
                {
                    text = userData->metaData.toHourMinuteSecond(buffer, sizeof(buffer));
                }
                if(lineNumbersEnabled&timeEnabled)
                {
                    text += " ";
                }
                if(lineNumbersEnabled)
                {
                    text += QString::number(userData->blockNr);
                }
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

bool ConsoleWidget::LineNumberAreaEvent(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);

        //find the relative line number
        QTextBlock block = firstVisibleBlock();
        int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        int bottom = top + (int) blockBoundingRect(block).height();
        while(top < helpEvent->y())
        {
            if(block.next().isVisible() == false)break;
            block = block.next();
            top = bottom;
            bottom = top + (int) blockBoundingRect(block).height();
        }
        block = block.previous();
        QString text;
        TextBlockWithMetaData* userData = dynamic_cast<TextBlockWithMetaData*>(block.userData());
        if(userData)
        {
             char buffer[32];
             text = "line " + QString::number(userData->blockNr);
             text += "\nat " + userData->metaData.toHourMinuteSecond(buffer, sizeof(buffer));
        }
        QToolTip::showText(helpEvent->globalPos(), text);

        return true;
    }
    return false;
}


