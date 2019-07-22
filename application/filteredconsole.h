#pragma once


#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QStandardItemModel>
#include <QSignalMapper>


#include "outputnode.h"
#include "tagfilter.h"


class FilteredConsole  : public QWidget, public InputNode
{
    Q_OBJECT
public:
    void clear();
    void NotifyBufferUpdate(Subscription *source)override;

    FilteredConsole();
    ~FilteredConsole();
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QVBoxLayout *layout = nullptr;
    QHBoxLayout *verticalLayout = nullptr;

    QList<QStandardItem*> items;
    QList<QStandardItemModel*> properyBoxes;
    QTextCharFormat currentCharFormat;
    QPlainTextEdit* console = nullptr;
    TagFilter *tagFilter = nullptr;

public slots:
    void propertyChanged(Property *property);
    void slot_changed(QObject *property);
};

