#include "visualserialnode.h"



VisualSerialNode::VisualSerialNode()
{
    node = new SerialNode();
    baseNode = node;
    name = "Serial node";
    if(node->hasInput)
    {
        addInputConnector();
    }
    if(node->hasOutput)
    {
        addOutputConnector();
    }
    connect(node,SIGNAL(SerialPortError(QSerialPort::SerialPortError)),this,SLOT(handleSerialPortError(QSerialPort::SerialPortError)));

    proxyWidget = new QGraphicsProxyWidget(this);
    portComboBox = new ComboBox();
    portComboBox->setStyleSheet("QComboBox{subcontrol-origin: padding;subcontrol-position: top right;selection-background-color: #111;selection-color: yellow;color: white;background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);border-style: solid;border: 1px solid #1e1e1e;border-radius: 5;padding: 1px 0px 1px 20px;}");
    proxyWidget->setWidget(portComboBox);
    proxyWidget->setPos(10,30);
    proxyWidget->setZValue(10000);
    connect(portComboBox,SIGNAL(onShowPopup(ComboBox*)),this,SLOT(loadSerialPorts()));
    connect(portComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxChanged()));

    baudRateProxyWidget = new QGraphicsProxyWidget(this);
    baudRateCombobox = new ComboBox();
    baudRateCombobox->setStyleSheet("QComboBox{subcontrol-origin: padding;subcontrol-position: top right;selection-background-color: #111;selection-color: yellow;color: white;background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);border-style: solid;border: 1px solid #1e1e1e;border-radius: 5;padding: 1px 0px 1px 20px;}");
    QList<qint32> baudrates = QSerialPortInfo::standardBaudRates();
    for(int i = 0;i<baudrates.size();i++)
    {
        baudRateCombobox->addItem(QString::number(baudrates[i]));
        if(baudrates[i] == defaultBaudRate)
        {
            baudRateCombobox->setCurrentIndex(i);
        }
    }
    baudRateProxyWidget->setWidget(baudRateCombobox);
    baudRateProxyWidget->setPos(10,50);
    connect(baudRateCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(onBaudRateChanged()));

    loadSerialPorts();

}
void VisualSerialNode::onBaudRateChanged()
{
    openPort();
}
void VisualSerialNode::onComboBoxChanged()
{
    if(activated)
    {
        if(!lockCombobox)
        {
            openPort();
        }
    }
}
VisualSerialNode::~VisualSerialNode()
{
    if(node != nullptr)
    {
        delete node;
        baseNode = nullptr;
    }
}
void VisualSerialNode::activate()
{
    activated = true;
}
void VisualSerialNode::openPort()
{
    node->closeSerialPort();
    if(portComboBox->count() > 0)
    {
        if(portComboBox->currentText().size() > 0)
        {
            node->settings->nodeSettings.name = portComboBox->currentText();
            node->settings->nodeSettings.baudRate = baudRateCombobox->currentText().toInt();
            node->openSerialPort();
        }
    }
}
VisualNodeBase* VisualSerialNode::clone()
{
    return new VisualSerialNode();
}
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);
    if(node->settings->nodeSettings.running)
    {
        height = 80;
    }
    else {
        height = 100;
    }
    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);
    drawStartStop(painter,node->settings->nodeSettings.running);
}
void VisualSerialNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(startStopClicked(event->pos()))
    {
        if(node->settings->nodeSettings.running)
        {
            node->closeSerialPort();
        }
        else {
            openPort();
        }
    }
    else {
        VisualSourceNodeBase::mousePressEvent(event);
    }
}
void VisualSerialNode::handleSerialPortError(QSerialPort::SerialPortError)
{
    loadSerialPorts();
}
void VisualSerialNode::loadSerialPorts()
{
    lockCombobox = true;
    QString lastText = portComboBox->currentText();
    portComboBox->clear();
    portComboBox->addItem("");
    int i = 1;
    int currentIndex = -1;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        portComboBox->addItem(info.portName());
        if(info.portName() == lastText)
        {
            currentIndex = i;
        }
        i++;
    }
    if(currentIndex != -1)
    {
        portComboBox->setCurrentIndex(i);
    }
    else {
        lockCombobox = false;
        onComboBoxChanged();
    }
    lockCombobox = false;

}
