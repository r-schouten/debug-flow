#pragma once

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <Qtooltip>

#include "textblockwithtimestamp.h"
#include "timestamphelper.h"
class ConsoleWidget: public QPlainTextEdit
{
    Q_OBJECT
public:
    ConsoleWidget(QWidget* parent = nullptr);
    void setMaxLines(int lines);
    int lineNumberAreaWidth();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    bool LineNumberAreaEvent(QEvent *event);
    void append(QString textToAdd, QTextCharFormat format, TimeStamp_t *timeStamp, bool autoScroll);
    virtual void clear();
    void setLineNumbersEnabled(bool enabled);
    void setTimeEnabled(bool enabled);
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    void resizeEvent(QResizeEvent *e);
    QWidget *lineNumberArea = nullptr;
    int maxBlockCount = 100;
    int oldBlockCount = 0;
    int deletedBlocks = 0;
    int oldAreaWidth = 0;

    bool lineNumbersEnabled = true;
    bool timeEnabled = false;
    bool sideLineEnabled = true;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ConsoleWidget *consoleWidget) : QWidget(consoleWidget),consoleWidget(consoleWidget) {
    }

    QSize sizeHint() const override {
        return QSize(consoleWidget->lineNumberAreaWidth(), 0);
    }
    bool event(QEvent *event)
    {
        if(consoleWidget->LineNumberAreaEvent(event))
        {
            return true;
        }
        return QWidget::event(event);
    }
protected:
    void paintEvent(QPaintEvent *event) override {
        consoleWidget->lineNumberAreaPaintEvent(event);
    }

private:
    ConsoleWidget *consoleWidget;

};
