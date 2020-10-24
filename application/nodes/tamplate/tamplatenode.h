#pragma once


#include "tamplatenodesettings.h"
#ifdef OUTPUTNODE
    #include "nodeoutput.h"
    #include "metadatahelper.h"
    #define TAMPLATE_BUFFER_SIZE 100000
#endif
#ifdef INPUTNODE
    #include "inputnode.h"
#endif


class TamplateNode :public NodeBase
{
public:
    TamplateNode(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~TamplateNode();
    virtual std::string getNodeName();
    virtual TamplateNodeSettings *getNodeSettings();
    void reset();

    virtual int amountOfInputs();
    virtual int amountOfOutputs();
    virtual NodeInput *getInput(int index);
    virtual NodeOutput *getOutput(int index);
#ifdef INPUTNODE
    void NotifyBufferUpdate(Subscription *source);
    void notifyHistoricalUpdateFinished();
#endif
protected:
    TamplateNodeSettings* settings = nullptr;

#ifdef OUTPUTNODE
    MetaDataHelper* metaDataHelper = nullptr;
    void dataReceived();
#endif
#ifdef INPUTNODE
    NodeInput* nodeInput = nullptr;
#endif
#ifdef OUTPUTNODE
    NodeOutput* nodeOutput = nullptr;
    CircularBuffer* circularBuffer = nullptr;
#endif


};

