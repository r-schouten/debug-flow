#pragma once
#include <QString>
#include "nodeInput.h"
#include "nodeoutput.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
#include "historicalupdatemanager.h"
class ContextFilterNode : public QObject, public NodeBase
{
    Q_OBJECT
public:
    ContextFilterNode(UpdateManager* updateManager, DbgLogger *dbgLogger, HistoricalUpdateManager* historicalUpdateManager);
    virtual ~ContextFilterNode();
    virtual std::string getNodeName() override;
    virtual ContextFilterSettings *getNodeSettings() override;
    virtual UpdateReturn_t doBufferUpdate(Subscription *source, int availableSize);
    virtual void reset() override;

    virtual int amountOfInputs() {return 1;}
    virtual int amountOfOutputs() {return 1;}
    virtual NodeInput *getInput(int index) {return nodeInput;}
    virtual NodeOutput *getOutput(int index) {return nodeOutput;}


private slots:
    void initiateHistoricalUpdate();

private:
    MetaData_t metaData;
    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;
    HistoricalUpdateManager* historcalUpdateManager = nullptr;

    NodeInput* nodeInput = nullptr;
    NodeOutput* nodeOutput = nullptr;
    CircularBuffer* circularBuffer = nullptr;
};

