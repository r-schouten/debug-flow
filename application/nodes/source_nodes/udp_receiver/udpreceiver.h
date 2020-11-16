#pragma once

#include <QUdpSocket>

#include "nodeoutput.h"
#include "metadatahelper.h"
#include "udpreceiversettings.h"
#define UDP_RECEIVER_BUFFER_SIZE 100000

class UdpReceiver : public QObject, public NodeBase
{
    Q_OBJECT

public:
    UdpReceiver(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~UdpReceiver();
    virtual std::string getNodeName();
    virtual UdpReceiverSettings *getNodeSettings();
    void reset();

    virtual int amountOfInputs()
        {return 0;}
    virtual int amountOfOutputs()
        {return 1;}
    virtual NodeInput *getInput(int index)
        {return nullptr;}
    virtual NodeOutput *getOutput(int index)
        {return nodeOutput;}

    void activate();
public slots:
    void readyRead();
protected:
    void configure();

    UdpReceiverSettings* settings = nullptr;

    MetaDataHelper* metaDataHelper = nullptr;

    NodeOutput* nodeOutput = nullptr;
    CircularBuffer* circularBuffer = nullptr;

    QUdpSocket *socket = nullptr;
};

