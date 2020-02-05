#pragma once


#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QCheckBox>
#include <QStandardItemModel>
#include <QSignalMapper>


#include "outputnode.h"
#include "contextfilter.h"
#include "filterednodesettings.h"
#include "filteredconsolewidgets.h"

class TagComboBox :public QComboBox
{
    Q_OBJECT
public:
    TagComboBox(Tag* tag)
        :tag(tag){

        itemModel = new QStandardItemModel();
        setModel(itemModel);
        connect(itemModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(itemChanged(QStandardItem*)));
        connect(tag,SIGNAL(dataChanged(Tag*)),this,SLOT(loadTag()));
    }
    Tag* tag = nullptr;
    QStandardItemModel* itemModel = nullptr;

public slots:
    void loadTag()
    {
        this->clear();

        QListIterator<TagOption*> optionIterator(tag->options);
        while(optionIterator.hasNext())
        {
            TagOption* currentOption = optionIterator.next();
            TagOptionItem* item = new TagOptionItem(currentOption);
            item->setText(currentOption->name);
            item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            item->setData(item->tagOption->enabled? Qt::Checked:Qt::Unchecked, Qt::CheckStateRole);
            itemModel->appendRow(item);
        }
    }
    void itemChanged(QStandardItem *item)
    {
        TagOptionItem* option = dynamic_cast<TagOptionItem*>(item);
        if(option)
        {
            option->tagOption->enabled = option->checkState();
            tag->notifyDataChanged();
        }
    }
private:
};


class FilteredConsole  : public QWidget, public InputNode
{
    Q_OBJECT
public:
    void clear();
    void NotifyBufferUpdate(Subscription *source)override;

    FilteredConsole();
    ~FilteredConsole();
    NodeSettingsBase *getNodeSettings();


    FilteredNodeSettings* nodeSettings = nullptr;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QList<TagComboBox*> tagComboBoxes;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *verticalLayout = nullptr;


    QTextCharFormat currentCharFormat;
    QPlainTextEdit* console = nullptr;
    ContextFilter *contextFilter = nullptr;

public slots:
    void optionAdded(Tag *tag, TagOption *option);
    void clearConsole();
    //void propertyChanged(Property *property);
    //void slot_changed(QObject *property);
private slots:
    void loadTags();
    void filterOnWindowChanged();
    void loadMaxLines();
    void loadScrollSettings();
};

