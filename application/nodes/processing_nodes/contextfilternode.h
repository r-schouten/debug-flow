#pragma once
#include "inputnode.h"
#include "outputnode.h"

#include "contextfiltersettings.h"
#include "contextfilterengine.h"
class ContextFilterNode : public QObject, public InputNode, public OutputNode
{
    Q_OBJECT
public:
    ContextFilterNode(DbgLogger *dbgLogger);
    virtual ~ContextFilterNode();
    ContextFilterSettings *getNodeSettings();
    void NotifyBufferUpdate(Subscription *source);

private slots:
    void initiateHistoricalUpdate();

protected:
    void leftHistoricalUpdateOccured();
private:
    bool filterData(CircularBuffer *destination, CircularBufferReader *bufferReader);

    ContextFilterSettings* settings = nullptr;
    ContextFilterEngine* contextFilterEngine = nullptr;

};

