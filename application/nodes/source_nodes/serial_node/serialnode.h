#pragma once
#include <QSerialPort>
#include <QMessageBox>

#include "nodeoutput.h"
#include "serialnodeinterface.h"
#include "serialsettings.h"
#include "metadatahelper.h"

class SerialNode :public QObject, public SerialNodeInterface
{
    Q_OBJECT
public:
    SerialNode(UpdateManager* updateManager,DbgLogger *dbgLogger);
    virtual ~SerialNode();

    virtual std::string getNodeName();

    void openSerialPort();
    void closeSerialPort();
    void writeData(const char* data, const size_t length);
    virtual void reset();
    void activate();

private:
    QSerialPort *m_serial = nullptr;
    MetaDataHelper* metaDataHelper = nullptr;
    bool activated = false;
public slots:
    void handleError(QSerialPort::SerialPortError error);
private slots:
    void readData();
};

