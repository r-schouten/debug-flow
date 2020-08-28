#pragma once
#include <QElapsedTimer>
#include "dbglogger.h"


#define MAX_AMOUNT_OF_MEAUSEMENTS 1000
enum UpdateReturn_t
{
    UPDATE_DONE,
    NOT_DONE,
    ROUTE_DELAYED
};
enum ProfileSource_t
{
    START,
    CONTEXT_FILTER_BEGIN,
    CONTEXT_FILTER_END,
    SUBSCRIPTION,
    FILTER_WITH_STYLE_START,
    FILTER_WITH_STYLE_END,
    ZERO_MEASUREMENT_START,
    ZERO_MEASUREMENT_END,
    MERGE_BEGIN,
    MERGE_END,
    VISUALIZE_BEGIN,
    VISUALIZE_END,
    FINISH
};
struct ProfilePoint
{
    ProfileSource_t source;
    int elapsed=0;
};

typedef uint64_t UpdateNr_t;

class OutputNode;
class UpdateManager
{
public:
    UpdateManager(DbgLogger* dbgLogger);

    UpdateNr_t initateUpdate(OutputNode* sourceNode);
    UpdateNr_t getUpdateNr();

    void measurementPoint(ProfileSource_t waitpoint);

    int depth = 0;

    void printMeasurement();
private:
    DbgLogger* dbgLogger = nullptr;
    UpdateNr_t updateNr = 0;

    int profileCounter = 0;
    ProfilePoint measurementList[MAX_AMOUNT_OF_MEAUSEMENTS];
    QElapsedTimer timer;
    QStringList profileSourceText = {"START","CONTEXT_FILTER_BEGIN","CONTEXT_FILTER_END","SUBSCRIPTION","FILTER_WITH_STYLE_START","FILTER_WITH_STYLE_END","ZERO_MEASUREMENT_START","ZERO_MEASUREMENT_END","MERGE_BEGIN","MERGE_END","VISUALIZE_BEGIN","VISUALIZE_END","FINISH"};

};

