#include "serialnodepropertieswidget.h"

#include <QGroupBox>
#include <QLabel>

SerialNodePropertiesWidget::SerialNodePropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, SerialNode *serialNode)
    :PropertyWidgetBase(parent,dbgLogger),serialNode(serialNode)
{    
    serialSettings = serialNode->getNodeSettings();

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setVerticalStretch(1);
    this->setSizePolicy(sizePolicy);

    layout = new QFormLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(10);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    availablePortsComboBox = new ComboBox();
    layout->addRow("port",availablePortsComboBox);
    loadAvailablePorts();

    //port labels

    errorLabel = new QLabel();
    errorLabel->setStyleSheet("QLabel { color : red; }");
    layout->addRow(errorLabel);

    manufacturerLabel = new QLabel();
    manufacturerLabel->setStyleSheet("QLabel { color : grey; }");
    layout->addRow(manufacturerLabel);

    descriptionLabel = new QLabel();
    descriptionLabel->setStyleSheet("QLabel { color : grey; }");
    layout->addRow(descriptionLabel);

    //load baud rates
    baudRatesComboBox = new QComboBox();
    bool baudrateFound = false;
    for(int i = 0;i<baudratesOptions.size();i++)
    {
        baudRatesComboBox->addItem(QString::number(baudratesOptions[i]));
        if(baudratesOptions[i] == serialSettings->baudRate)
        {
            baudRatesComboBox->setCurrentIndex(i);
            baudrateFound = true;
        }
    }
    baudRatesComboBox->addItem("custom");
    layout->addRow("baud rate",baudRatesComboBox);

    //custom baud rate
    customBaudRateEdit = new QLineEdit();
    validator = new QIntValidator(0, 5000000, this);
    customBaudRateEdit->setValidator(validator);
    customBaudRateEdit->hide();
    layout->addWidget(customBaudRateEdit);
    if(!baudrateFound)
    {
        baudRatesComboBox->setCurrentIndex(baudRatesComboBox->count()-1);//set to custom
        customBaudRateEdit->show();
        customBaudRateEdit->setText(QString::number(serialSettings->baudRate));
    }

    //data bits
    dataBitsBox = new QComboBox();
    dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    bool found = false;
    for(int i=0;i<dataBitsBox->count();i++)
    {
        if(dataBitsBox->itemData(i) == serialSettings->dataBits)
        {
            dataBitsBox->setCurrentIndex(i);
            found = true;
        }
    }
    if(found == false)
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"databits not found");
    }
    layout->addRow("data bits",dataBitsBox);

    //stopbits
    stopBitsBox = new QComboBox();
    stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    found = false;
    for(int i=0;i<stopBitsBox->count();i++)
    {
        if(stopBitsBox->itemData(i) == serialSettings->stopBits)
        {
            stopBitsBox->setCurrentIndex(i);
            found = true;
        }
    }
    if(found == false)
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"stopBits not found");
    }
    layout->addRow("stop bits",stopBitsBox);

    parityCombobox = new QComboBox();
    parityCombobox->addItem(tr("None"), QSerialPort::NoParity);
    parityCombobox->addItem(tr("Even"), QSerialPort::EvenParity);
    parityCombobox->addItem(tr("Odd"), QSerialPort::OddParity);
    parityCombobox->addItem(tr("Mark"), QSerialPort::MarkParity);
    parityCombobox->addItem(tr("Space"), QSerialPort::SpaceParity);
    found = false;
    for(int i=0;i<parityCombobox->count();i++)
    {
        if(parityCombobox->itemData(i) == serialSettings->parity)
        {
            parityCombobox->setCurrentIndex(i);
            found = true;
        }
    }
    if(found == false)
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"parity not found");
    }
    layout->addRow("parity",parityCombobox);

    flowControlBox = new QComboBox();
    flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
    found = false;
    for(int i=0;i<flowControlBox->count();i++)
    {
        if(flowControlBox->itemData(i) == serialSettings->flowControl)
        {
            flowControlBox->setCurrentIndex(i);
            found = true;
        }
    }
    if(found == false)
    {
        dbgLogger->error(CLASSNAME,__FUNCTION__,"flowcontrol not found");
    }
    layout->addRow("flow control",flowControlBox);

    connectButton  = new QPushButton("connect");
    disconnectButton  = new QPushButton("disconnect");
    layout->addRow(disconnectButton,connectButton);
    updateButtonStates();

    hideDeviceInfo();

    connect(availablePortsComboBox,SIGNAL(onShowPopup(ComboBox*)),this,SLOT(loadAvailablePorts()));
    connect(serialSettings,SIGNAL(SerialErrorOccured()),this,SLOT(handleSerialPortError()));
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectClicked()));
    connect(disconnectButton,SIGNAL(clicked()),this,SLOT(disconnectClicked()));

    connect(availablePortsComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));
    connect(customBaudRateEdit,SIGNAL(textChanged(QString)),this,SLOT(settingsChanged()));
    connect(baudRatesComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));
    connect(dataBitsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));
    connect(stopBitsBox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));
    connect(parityCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));
    connect(flowControlBox,SIGNAL(currentIndexChanged(int)),this,SLOT(settingsChanged()));


}

SerialNodePropertiesWidget::~SerialNodePropertiesWidget()
{
    delete validator;
}
void SerialNodePropertiesWidget::hideDeviceInfo()
{
    errorLabel->hide();
    manufacturerLabel->hide();
    descriptionLabel->hide();
}

void SerialNodePropertiesWidget::updateDeviceInfo()
{
    if(availablePortsComboBox->currentData().toString() == "")
    {
        hideDeviceInfo();
        return;
    }
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(info.portName() == availablePortsComboBox->currentData().toString())
        {
            if(info.manufacturer() != "")
            {
                manufacturerLabel->show();
                manufacturerLabel->setText(info.manufacturer());
            }
            else {
                manufacturerLabel->hide();
            }
            if(info.description() != "")
            {
                descriptionLabel->show();
                descriptionLabel->setText(info.description());
            }
            else {
                descriptionLabel->hide();
            }

        }

    }
    if(serialSettings->errorOccured)
    {
        errorLabel->show();
        errorLabel->setText("ERROR: " + serialSettings->errorString);
    }
    else {
        errorLabel->hide();
    }
}
void SerialNodePropertiesWidget::loadAvailablePorts()
{
    availablePortsComboBox->clear();
    availablePortsComboBox->addItem("","");
    int i = 1;
    int currentIndex = -1;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString text = info.portName();
        if(info.portName() == serialSettings->name)
        {
            currentIndex = i;
            if(serialSettings->running)
            {//show that the port is already open
                text += "-current";
            }
        }
        else {
            if(info.isBusy())
            {
                text += "-busy";
            }
            if(info.isNull())
            {
                text += "-null";
            }
        }
        availablePortsComboBox->addItem(text,info.portName());
        availablePortsComboBox->setItemData(availablePortsComboBox->count()-1,info.description(), Qt::ToolTipRole);
        i++;
    }
    if(currentIndex != -1)
    {
        availablePortsComboBox->setCurrentIndex(currentIndex);
    }
}

bool SerialNodePropertiesWidget::IsPortAvailable()
{
    if(availablePortsComboBox->currentData().toString() == "")
    {
        return false;
    }
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(info.portName() == availablePortsComboBox->currentData().toString())
        {
            if(info.isBusy() || info.isNull())
            {
                if(info.portName() == serialSettings->name)
                {
                    //port is currently busy because the current node is using it
                }
                else {
                    //port is used by an other node or program
                    return false;
                }
            }
            return true;

        }

    }
    return false;
}
void SerialNodePropertiesWidget::handleSerialPortError()
{
    updateButtonStates();
}
void SerialNodePropertiesWidget::connectClicked()
{
    if(!IsPortAvailable())
    {
        //don't connect if the port is not valid
        return;
    }
    serialSettings->name = availablePortsComboBox->currentData().toString();
    serialSettings->parity = static_cast<QSerialPort::Parity>(
                parityCombobox->itemData(parityCombobox->currentIndex()).toInt());
    if(baudRatesComboBox->currentIndex() == baudRatesComboBox->count()-1)//custom baud rate
    {
        serialSettings->baudRate = customBaudRateEdit->text().toInt();
    }
    else //standard baud rate
    {
        serialSettings->baudRate = baudRatesComboBox->currentText().toInt();
    }
    serialSettings->dataBits = static_cast<QSerialPort::DataBits>(
                dataBitsBox->itemData(dataBitsBox->currentIndex()).toInt());
    serialSettings->stopBits = static_cast<QSerialPort::StopBits>(
                stopBitsBox->itemData(stopBitsBox->currentIndex()).toInt());
    serialSettings->flowControl = static_cast<QSerialPort::FlowControl>(
                flowControlBox->itemData(flowControlBox->currentIndex()).toInt());

    if(serialSettings->running)
    {
        serialNode->closeSerialPort();
    }
    serialNode->openSerialPort();

    settingChanged = false;
    updateButtonStates();
    serialSettings->print();

    emit serialSettings->notifySettingsChanged();
}
void SerialNodePropertiesWidget::disconnectClicked()
{
    if(serialSettings->running)
    {
        serialNode->closeSerialPort();
    }
    updateButtonStates();
}
void SerialNodePropertiesWidget::settingsChanged()
{
    dbgLogger->debug(CLASSNAME,__FUNCTION__,"settingsChanged");
    settingChanged = true;
    updateButtonStates();
    emit serialSettings->notifySettingsChanged();
}
void SerialNodePropertiesWidget::updateButtonStates()
{
    if(serialSettings->running)
    {
        disconnectButton->setEnabled(true);
        connectButton->setText("apply");
    }
    else
    {
        disconnectButton->setEnabled(false);
        connectButton->setText("connect");
    }
    if(IsPortAvailable())
    {
        if((serialSettings->running)&&(!settingChanged))//no setting is changed clicking the button would have no effect
        {
            connectButton->setEnabled(false);
        }
        else {
            connectButton->setEnabled(true);
        }
    }
    else {
        connectButton->setEnabled(false);
    }
    updateDeviceInfo();
}

