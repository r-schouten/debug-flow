#include "serialnode.h"

SerialNode::SerialNode()
{
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);
}
SerialNode::~SerialNode()
{
    delete m_serial;
}
void SerialNode::openSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
        qDebug("[Debug][SerialNode] close before open");
    }
    settings->running = false;

    qDebug("%s",settings->name.toStdString().c_str());

    m_serial->setPortName(settings->name);
    m_serial->setBaudRate(settings->baudRate);
    m_serial->setDataBits(settings->dataBits);
    m_serial->setParity(settings->parity);
    m_serial->setStopBits(settings->stopBits);
    m_serial->setFlowControl(settings->flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug("[Debug][SerialNode] connected");
        settings->running = true;
        settings->errorOccured = false;
    } else {
        settings->running = false;
        settings->errorOccured = true;
        settings->errorString = m_serial->errorString();
        qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
        settings->print();
        settings->notifySettingsChanged(DATA_VALID, SAVE,  NODE);
    }
}

void SerialNode::closeSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
        qDebug("Disconnected");
    }
    settings->running = false;
    settings->notifySettingsChanged(DATA_VALID, SAVE, NODE);
}

void SerialNode::writeData(const char* data, const size_t length)
{
    m_serial->write(data, length);
}

void SerialNode::readData()
{
    QByteArray data = m_serial->readAll();
    circularBuffer->append(&data);
    NotifyAllSubscriptions();
}
void SerialNode::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        qDebug("[Error][SerialNode]- %s", m_serial->errorString().toStdString().c_str());
        settings->errorOccured = true;
        settings->errorString = m_serial->errorString();
        closeSerialPort();
    }
}
