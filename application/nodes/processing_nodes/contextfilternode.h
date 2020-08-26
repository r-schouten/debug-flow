#pragma once
#include <QString>
#include "inputnode.h"
#include "outputnode.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
#include "historicalupdatemanager.h"
class ContextFilterNode : public QObject, public InputNode, public OutputNode
{
    Q_OBJECT
public:
    ContextFilterNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager* historicalUpdateManager);
    virtual ~ContextFilterNode();
    virtual std::string getNodeName() override;
    virtual ContextFilterSettings *getNodeSettings() override;
    virtual void doBufferUpdate(Subscription *source, int availableSize) override;
    virtual void reset() override;

private slots:
    void initiateHistoricalUpdate();

private:
    void filterData(CircularBuffer *buffer, CircularBufferReader *bufferReader);
    MetaData_t metaData;
    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;
    HistoricalUpdateManager* historcalUpdateManager = nullptr;

};

