#pragma once
#include "inputnode.h"
#include "outputnode.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
#include "historicalupdatemanager.h"
class ContextFilterNode : public QObject, public InputNode, public OutputNode
{
    Q_OBJECT
public:
    ContextFilterNode(DbgLogger *dbgLogger, HistoricalUpdateManager* historicalUpdateManager);
    virtual ~ContextFilterNode();
     virtual std::string getNodeName();
    ContextFilterSettings *getNodeSettings();
    void NotifyBufferUpdate(Subscription *source);
    virtual void reset();

private slots:
    void initiateHistoricalUpdate();

private:
    bool filterData(CircularBuffer *destination, CircularBufferReader *bufferReader);

    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;

    HistoricalUpdateManager* historcalUpdateManager = nullptr;
};

