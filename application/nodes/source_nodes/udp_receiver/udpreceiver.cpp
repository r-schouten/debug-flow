#include "udpreceiver.h"


UdpReceiver::UdpReceiver(UpdateManager *updateManager, DbgLogger *dbgLogger)
    :NodeBase(updateManager,dbgLogger)
{
    circularBuffer = new CircularBuffer(dbgLogger,"tamplate", UDP_RECEIVER_BUFFER_SIZE, UDP_RECEIVER_BUFFER_SIZE, true);
    nodeOutput = new NodeOutput(updateManager, circularBuffer, dbgLogger, this);

    settings = new UdpReceiverSettings(dbgLogger);
    metaDataHelper = new MetaDataHelper;


}

UdpReceiver::~UdpReceiver()
{
    delete nodeOutput;
    delete settings;
}

string UdpReceiver::getNodeName()
{
    return "UDP receiver";
}

UdpReceiverSettings *UdpReceiver::getNodeSettings()
{
    return settings;
}

void UdpReceiver::reset()
{

}
void UdpReceiver::activate()
{
    dbgLogger->debug("UdpReceiver", __FUNCTION__,"setup udp");

    socket = new QUdpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    configure();
}
void UdpReceiver::configure()
{
    socket->close();
    socket->bind(settings->getUdp_port());
}
void UdpReceiver::readyRead() //will be called when data is received on the udp interface
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);

    //qDebug() << "Message From: " << sender.toString() << " " << senderPort;

    //the current implementation is slow, it could be made better.
    //it is acceptable now because this code doesn't run in a historical update
    for(int i=0;i<Buffer.length();i++)
    {
        char a = Buffer.at(i);
        if(a == '[')
        {
            if(!((i !=0)&&(Buffer.at(i-1)=='\033')))
            {
                metaDataHelper->appendTime(circularBuffer);
            }
        }
        circularBuffer->appendByte(a);
    }
    updateManager->initateUpdate(nodeOutput);
}
