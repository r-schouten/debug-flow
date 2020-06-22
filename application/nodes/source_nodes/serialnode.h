#pragma once
#include <QSerialPort>
#include <QMessageBox>

#include "outputnode.h"
#include "serialnodeinterface.h"
#include "serialsettings.h"

class SerialNode :public QObject, public SerialNodeInterface
{
    Q_OBJECT
public:
    SerialNode(DbgLogger *dbgLogger);
    virtual ~SerialNode();

    void openSerialPort();
    void closeSerialPort();
    void writeData(const char* data, const size_t length);

private:
    QSerialPort *m_serial = nullptr;
public slots:
    void handleError(QSerialPort::SerialPortError error);
private slots:
    void readData();
};

