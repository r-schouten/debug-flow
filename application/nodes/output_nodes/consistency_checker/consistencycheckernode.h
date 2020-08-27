#pragma once

#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QRegExp>

#include <QApplication>
#include <QThread>
#include <QMutexLocker>

#include "consistencycheckersettings.h"
#include "inputnode.h"
#include "historicalupdatemanager.h"

#include "contextfilterengine.h"
#include "metadatahelper.h"
#include "tagandoptionssettings.h"

class ConsistencyCheckerNode :public QWidget, public InputNode
{
    Q_OBJECT
public:
    ConsistencyCheckerNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager* historcalUpdateManager);
    virtual ~ConsistencyCheckerNode();
    virtual std::string getNodeName();
    virtual ConsistencyCheckerSettings *getNodeSettings();
    void reset();
    UpdateReturn_t doBufferUpdate(Subscription *source, int availableSize);
    void notifyHistoricalUpdateFinished();
protected:
    ConsistencyCheckerSettings* settings = nullptr;
    HistoricalUpdateManager* historcalUpdateManager = nullptr;
    QVBoxLayout *layout = nullptr;
    QPlainTextEdit* console = nullptr;

    ContextFilterEngine* contextFilterEngine = nullptr;
    TagAndOptionsSettings* tagAndOptionsSettings = nullptr;
private slots:
    void initiateHistoricalUpdate();
private:
    void appendConsole(QString text);
    QString match = "[debug, testdata] this should match exactly ";
    int lastNr = 0;
    QString bufferString;
    QString bufferStringCopy;
    QMutex classMutex;
};

