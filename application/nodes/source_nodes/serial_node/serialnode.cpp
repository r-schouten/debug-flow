#include "serialnode.h"

SerialNode::SerialNode(UpdateManager* updateManager,DbgLogger *dbgLogger)
    :SerialNodeInterface(updateManager,dbgLogger)
{
    settings = new SerialSettings(dbgLogger);
}


SerialNode::~SerialNode()
{
    delete m_serial;
}

void SerialNode::activate()
{
    activated = true;


    m_serial = new QSerialPort(this);
    metaDataHelper = new MetaDataHelper;
    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);
}
void SerialNode::reset()
{

}
std::string SerialNode::getNodeName()
{
    return CLASSNAME;
}
void SerialNode::openSerialPort()
{
    if(!activated) return;
    if (m_serial->isOpen())
    {
        m_serial->close();
        dbgLogger->debug(CLASSNAME,__FUNCTION__," close before open");
    }
    settings->running = false;

    dbgLogger->debug(CLASSNAME,__FUNCTION__,"%s",settings->name.toStdString().c_str());

    m_serial->setPortName(settings->name);
    m_serial->setBaudRate(settings->baudRate);
    m_serial->setDataBits(settings->dataBits);
    m_serial->setParity(settings->parity);
    m_serial->setStopBits(settings->stopBits);
    m_serial->setFlowControl(settings->flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        dbgLogger->debug(CLASSNAME,__FUNCTION__," connected");
        settings->running = true;
        settings->errorOccured = false;
    } else {
        settings->running = false;
        settings->errorOccured = true;
        settings->errorString = m_serial->errorString();
        dbgLogger->error(CLASSNAME,__FUNCTION__," %s", m_serial->errorString().toStdString().c_str());
        settings->print();
        settings->notifySettingsChanged(DATA_VALID, SAVE,  NODE);
    }
}

void SerialNode::closeSerialPort()
{
    if(!activated)return;
    if (m_serial->isOpen())
    {
        m_serial->close();
        dbgLogger->debug(CLASSNAME,__FUNCTION__,"Disconnected");
    }
    settings->running = false;
    settings->notifySettingsChanged(DATA_VALID, SAVE, NODE);
}

void SerialNode::writeData(const char* data, const size_t length)
{
    if(!activated) return;
    m_serial->write(data, length);
}

void SerialNode::readData()
{
    if(!activated) return;
    QByteArray data = m_serial->readAll();

    //the current implementation is slow, it could be made better.
    //it is acceptable now because this code doesn't run in a historical update
    for(int i=0;i<data.length();i++)
    {
        char a = data.at(i);
        if(a == '[')
        {
            if(!((i !=0)&&(data.at(i-1)=='\033')))
            {
                metaDataHelper->appendTime(circularBuffer);
            }
        }
        circularBuffer->appendByte(a);
    }
    updateManager->initateUpdate(nodeOutput);
}
void SerialNode::handleError(QSerialPort::SerialPortError error)
{
    if(!activated) return;
    if (error != QSerialPort::NoError) {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"- %s", m_serial->errorString().toStdString().c_str());
        settings->errorOccured = true;
        settings->errorString = m_serial->errorString();
        closeSerialPort();
        emit settings->SerialErrorOccured();
    }
}
