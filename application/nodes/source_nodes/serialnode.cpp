#include "serialnode.h"

#include <QThread>

SerialNode::SerialNode::SerialNode(DbgLogger *dbgLogger)
    :NodeBase(dbgLogger),SerialNodeInterface(dbgLogger)
{
    m_serial = new QSerialPort(this);
    metaDataHelper = new MetaDataHelper;
    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);
}


SerialNode::~SerialNode()
{
    delete m_serial;
}

std::string SerialNode::getNodeName()
{
    return CLASSNAME;
}
void SerialNode::openSerialPort()
{
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
    m_serial->write(data, length);
}

void SerialNode::reset()
{

}

void SerialNode::readData()
{
    QByteArray data = m_serial->readAll();

    metaDataHelper->appendTime(circularBuffer);
    circularBuffer->append(&data);
    notifyAllSubscriptions();
}
void SerialNode::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"- %s", m_serial->errorString().toStdString().c_str());
        settings->errorOccured = true;
        settings->errorString = m_serial->errorString();
        closeSerialPort();
        emit settings->SerialErrorOccured();
    }
}
