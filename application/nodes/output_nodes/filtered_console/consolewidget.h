#pragma once

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>

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
    void append(QString textToAdd, QTextCharFormat format, TimeStamp_t *timeStamp, bool autoScroll);
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
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ConsoleWidget *consoleWidget) : QWidget(consoleWidget),consoleWidget(consoleWidget) {
    }

    QSize sizeHint() const override {
        return QSize(consoleWidget->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        consoleWidget->lineNumberAreaPaintEvent(event);
    }

private:
    ConsoleWidget *consoleWidget;
};
