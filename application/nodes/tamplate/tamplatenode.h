#pragma once


#include "tamplatenodesettings.h"
#ifdef OUTPUTNODE
    #include "outputnode.h"
    #include "metadatahelper.h"
    #define TAMPLATE_BUFFER_SIZE 100000
#endif
#ifdef INPUTNODE
    #include "inputnode.h"
#endif

#if defined (OUTPUTNODE) && defined (INPUTNODE)
class TamplateNode :public OutputNode, public InputNode
#else
#ifdef OUTPUTNODE
class TamplateNode :public OutputNode
#endif
#ifdef INPUTNODE
class TamplateNode :public InputNode
#endif
#endif
{
public:
    TamplateNode(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~TamplateNode();
    virtual std::string getNodeName();
    virtual TamplateNodeSettings *getNodeSettings();
    void reset();
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


};

