#include "contextfilter.h"

ContextFilter::ContextFilter()
{
    if(dynamic_cast<InputNode*>(this))
    {
        hasInput = true;
    }
    if(dynamic_cast<OutputNode*>(this))
    {
        hasOutput = true;
    }
}

void ContextFilter::NotifyBufferUpdate(Subscription *source)
{
    qDebug("[verbose,ContextFilter,Q_FUNC_INFO] NotifyBufferUpdate");
}
