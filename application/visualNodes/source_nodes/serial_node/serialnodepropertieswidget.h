#pragma once
#include <QLineEdit>
#include <QPushButton>
#include <QSerialPortInfo>

#include "combobox.h"
#include "serialsettings.h"
#include "propertywidgetbase.h"
#include "serialnode.h"

class SerialNodePropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    SerialNodePropertiesWidget(QWidget *parent, SerialNode *serialNode);
    ~SerialNodePropertiesWidget();
public slots:
    void loadAvailablePorts();

    void connectClicked();
    void handleSerialPortError(QSerialPort::SerialPortError error);
    void disconnectClicked();
    void settingsChanged();
private:
    SerialNode* serialNode = nullptr;
    SerialSettings* serialSettings = nullptr;
    QList<qint32> baudratesOptions = {110,300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600,74880, 115200, 128000,230400 ,250000, 256000,460800,500000,921600,1000000,2000000};

    ComboBox* availablePortsComboBox = nullptr;
    QComboBox* baudRatesComboBox = nullptr;
    QLineEdit* customBaudRateEdit  = nullptr;
    QComboBox* parityCombobox = nullptr;
    QComboBox* dataBitsBox = nullptr;
    QComboBox* stopBitsBox = nullptr;
    QComboBox* flowControlBox = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* disconnectButton = nullptr;
    QIntValidator* validator = nullptr;
    QLabel* manufacturerLabel = nullptr;
    QLabel* descriptionLabel = nullptr;

    bool settingChanged = false;
    bool IsPortAvailable();
    void updateButtonStates();
    void hideDeviceInfo();
    void showDeviceInfo();
    void updateDeviceInfo();
};
