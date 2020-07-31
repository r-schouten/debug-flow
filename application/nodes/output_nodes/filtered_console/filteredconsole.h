#pragma once

#include <QHBoxLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QCheckBox>
#include <QStandardItemModel>
#include <QSignalMapper>

#include "consolewidget.h"
#include "outputnode.h"
#include "contextfilterengine.h"
#include "filterednodesettings.h"
#include "tag-option-item.h"
#include "historicalupdatemanager.h"
#include "timestamphelper.h"
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
    FilteredConsole(DbgLogger *dbgLogger, HistoricalUpdateManager *historcalUpdateManager);
    virtual ~FilteredConsole();

    void NotifyBufferUpdate(Subscription *source)override;
    void notifyHistoricalUpdateFinished() override;


    NodeSettingsBase *getNodeSettings();
    virtual std::string getNodeName();
    FilteredNodeSettings* nodeSettings = nullptr;

    virtual void reset();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QList<TagComboBox*> tagComboBoxes;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *verticalLayout = nullptr;

    ConsoleWidget* console = nullptr;
    ContextFilterEngine *contextFilter = nullptr;
    HistoricalUpdateManager* historcalUpdateManager = nullptr;

    QString bufferString;
    QTextCharFormat currentCharFormat;
    TimeStamp_t timeStamp;
    void filterData(CircularBufferReader *bufferReader);
public slots:
    void optionAdded(Tag *tag, TagOption *option);
    void clearConsole();
private slots:
    void loadTags();
    void filterOnWindowChanged();
    void loadMaxLines();
    void loadScrollSettings();

    void initiateHistoricalUpdate();
};
