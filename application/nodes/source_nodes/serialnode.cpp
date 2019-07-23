#include "serialnode.h"

SerialNode::SerialNode()
{
    if(dynamic_cast<InputNode*>(this))
    {
        hasInput = true;
    }
    if(dynamic_cast<OutputNode*>(this))
    {
        hasOutput = true;
    }
    settings = new SerialSettingsBase();
    circularBuffer = new CircularBuffer(1000,10000);
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);

}
void SerialNode::openSerialPort()
{
    qDebug("%s",settings->settings().name.toStdString().c_str());
    const SerialSettingsBase::Settings p = settings->settings();
    qDebug("%s",p.name.toStdString().c_str());

    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {

    } else {

       qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
       settings->print();
    }
}

void SerialNode::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    qDebug("Disconnected");
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
    if (error == QSerialPort::ResourceError) {
        qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
        closeSerialPort();
    }
}
