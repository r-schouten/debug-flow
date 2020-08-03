#include "contextfilternode.h"

ContextFilterNode::ContextFilterNode(DbgLogger *dbgLogger, HistoricalUpdateManager *historicalUpdateManager)
    :NodeBase(dbgLogger),historcalUpdateManager(historicalUpdateManager)
{
    circularBuffer = new CircularBuffer(dbgLogger);
    settings = new ContextFilterSettings(dbgLogger);
    connect(settings,SIGNAL(notifyDataInvalid()), this, SLOT(initiateHistoricalUpdate()));

    contextFilterEngine = new ContextFilterEngine(settings->tagAndOptionsSettings,dbgLogger);

}


ContextFilterNode::~ContextFilterNode()
{
    delete settings;
    settings = nullptr;
    delete contextFilterEngine;
}

std::string ContextFilterNode::getNodeName()
{
    return CLASSNAME;
}
ContextFilterSettings *ContextFilterNode::getNodeSettings()
{
    return settings;
}

void ContextFilterNode::filterData(CircularBuffer* buffer, CircularBufferReader *bufferReader)
{
    auto lambda = [&](char character) mutable {buffer->appendByte(&character);};

    OutputNode* outputNode = dynamic_cast<OutputNode*>(this);
    contextFilterEngine->filterData(lambda, bufferReader, bufferReader->availableSize(), outputNode->getBufferUnusedSize(), &processingDone,&metaData);
}

void ContextFilterNode::NotifyBufferUpdate(Subscription *source)
{
    if(source->bufferReader == nullptr){
        qFatal("ContextFilterNode::notifyBufferUpdate() : bufferReader == nullptr");
    }

    filterData(circularBuffer, source->bufferReader);

    notifyAllSubscriptions();
}


void ContextFilterNode::reset()
{

}
void ContextFilterNode::initiateHistoricalUpdate()
{
    historcalUpdateManager->initatiateHistoricalUpdate(this);
}
