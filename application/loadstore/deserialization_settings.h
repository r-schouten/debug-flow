#pragma once

#include "serialization_error_log.h"


class DeserializationSettings_t
{
public:
    bool restoreContext = true;
    bool restoreData = false; //if supported
    bool returnOnError = true;
    bool returnOnFatal = true;
    bool needToReturn(SerializationErrorLog &errorLog)
    {
        if((errorLog.fatalErrorOccured) && (returnOnFatal))
        {
            return true;
        }
        if((errorLog.errorOccured) && (returnOnError))
        {
            return true;
        }
        return false;
    }
};
