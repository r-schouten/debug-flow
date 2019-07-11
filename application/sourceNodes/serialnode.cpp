#include "serialnode.h"

SerialNode::SerialNode(SettingsDialog* settingDialog)
    :m_settings(settingDialog)
{
    circularBuffer = new CircularBuffer(1000,10000);
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialNode::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialNode::readData);
}
void SerialNode::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
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
        //QMessageBox::critical(this, tr("Error"), m_serial->errorString());

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
    //showStatusMessage(tr("Disconnected"));
}
void SerialNode::writeData(const QByteArray &data)
{
    m_serial->write(data);
}
void SerialNode::readData()
{
    QByteArray data = m_serial->readAll();
    circularBuffer->append(&data);
    //circularBuffer->print();

    NotifyAllSubscriptions();
}

void SerialNode::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        //QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}
