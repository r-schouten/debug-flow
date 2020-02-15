#include "serialnode.h"

SerialNode::SerialNode()
{
    settings = new SerialSettings();
    circularBuffer = new CircularBuffer(100000,1000000);
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);
}
SerialNode::~SerialNode()
{
    delete settings;
    delete m_serial;
}
NodeSettingsBase *SerialNode::getNodeSettings()
{
    return settings;
}
void SerialNode::openSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
        qDebug("[Debug][SerialNode] close before open");
    }
    settings->nodeSettings.running = false;

    const SerialSettings::Settings p = settings->settings();
    qDebug("%s",p.name.toStdString().c_str());

    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug("[Debug][SerialNode] connected");
        settings->nodeSettings.running = true;
        settings->nodeSettings.errorOccured = false;
    } else {
        settings->nodeSettings.running = false;
        settings->nodeSettings.errorOccured = true;
        settings->nodeSettings.errorString = m_serial->errorString();
        qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
        settings->print();
    }
}

void SerialNode::closeSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
        qDebug("Disconnected");
    }
    settings->nodeSettings.running = false;
}
void SerialNode::writeData(const QByteArray &data)
{
    m_serial->write(data);
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
        settings->nodeSettings.errorOccured = true;
        settings->nodeSettings.errorString = m_serial->errorString();
        closeSerialPort();
        emit SerialPortError(error);
    }
}
