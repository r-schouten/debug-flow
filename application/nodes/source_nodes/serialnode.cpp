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

    m_settings = new SettingsDialog();
    circularBuffer = new CircularBuffer(1000,10000);
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);

}
void SerialNode::openSerialPort()
{
    qDebug("%s",m_settings->settings().name.toStdString().c_str());
    const SettingsDialog::Settings p = m_settings->settings();
    qDebug("%s",p.name.toStdString().c_str());

    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        //m_ui->actionConnect->setEnabled(false);
        //m_ui->actionDisconnect->setEnabled(true);
        //m_ui->actionConfigure->setEnabled(false);
        //showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
        //                  .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
        //                  .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
       qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
        qDebug("[Error][SerialNode] %d", m_serial->error());
        //showStatusMessage(tr("Open error"));
    }
}

void SerialNode::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    //filteredConsole->setEnabled(false);
    //m_ui->actionConnect->setEnabled(true);
    //m_ui->actionDisconnect->setEnabled(false);
    //m_ui->actionConfigure->setEnabled(true);
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

void SerialNode::openSettings()
{
    m_settings->show();
}

void SerialNode::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug("[Error][SerialNode] %s", m_serial->errorString().toStdString().c_str());
        closeSerialPort();
    }
}
