#pragma once

#include <QTimer>
#include <QRandomGenerator>
#include <QDataStream>
#include <QThread>
#include "outputnode.h"
#include "testgeneratorsettings.h"
#include "metadatahelper.h"
#include "utils.h"
#include "testgeneratorworker.h"


#define TEST_GENERATOR_BUFFER_SIZE 10000
#define TEST_GENERATOR_MAX_BUFFER_SIZE 1000000

class TestGeneratorNode : public QObject, public OutputNode
{
    Q_OBJECT
public:
    TestGeneratorNode(DbgLogger *dbgLogger);
    virtual ~TestGeneratorNode();
    virtual std::string getNodeName();
    virtual TestGeneratorSettings *getNodeSettings();
    void reset();

    void activate();
protected:
    TestGeneratorSettings* settings = nullptr;
    MetaDataHelper* metaDataHelper = nullptr;

    QTimer* updateTimer = nullptr;
    TestGeneratorWorker* worker = nullptr;
    QThread* workerThread  = nullptr;
    bool activated = false;


    bool generateData();

private slots:
    void updateRateChanged();
    void updateDone();
    void threadSettingsChanged();
    void processInMainThread();
};

