#pragma once

#include <QTimer>
#include <QDataStream>
#include <QThread>
#include <QApplication>
#include "nodeoutput.h"
#include "testgeneratorsettings.h"
#include "metadatahelper.h"
#include "utils.h"
#include "testgeneratorworker.h"

#define TEST_GENERATOR_BUFFER_SIZE 100000
#define TEST_GENERATOR_MAX_BUFFER_SIZE 1000000

class TestGeneratorNode : public QObject, public NodeBase
{
    Q_OBJECT
public:
    TestGeneratorNode(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~TestGeneratorNode();
    virtual std::string getNodeName();
    virtual TestGeneratorSettings *getNodeSettings();
    void reset();

    void activate();

    int amountOfInputs(){return 0;}
    int amountOfOutputs(){return 1;}
    NodeInput *getInput(int index){return nullptr;}
    NodeOutput *getOutput(int index){return nodeOutput;}
protected:
    TestGeneratorSettings* settings = nullptr;
    MetaDataHelper* metaDataHelper = nullptr;

    QTimer* updateTimer = nullptr;
    TestGeneratorWorker* worker = nullptr;
    TestGeneratorWorker* workerFromThread = nullptr;
    QThread* workerThread  = nullptr;
    bool activated = false;


    bool generateData();

    NodeOutput* nodeOutput = nullptr;
    CircularBuffer* circularBuffer = nullptr;
private slots:
    void updateRateChanged();
    void threadSettingsChanged();
    void processInMainThread();
    void updateDone();
};

