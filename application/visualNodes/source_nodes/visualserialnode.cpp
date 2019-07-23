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
    proxyWidget = new QGraphicsProxyWidget(this);
    portComboBox = new ComboBox();
    portComboBox->setStyleSheet("QComboBox{subcontrol-origin: padding;subcontrol-position: top right;selection-background-color: #111;selection-color: yellow;color: white;background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);border-style: solid;border: 1px solid #1e1e1e;border-radius: 5;padding: 1px 0px 1px 20px;}");
    proxyWidget->setWidget(portComboBox);
    proxyWidget->setPos(10,30);
    connect(portComboBox,SIGNAL(onShowPopup(ComboBox*)),this,SLOT(onComboBoxPopup(ComboBox*)));
    connect(portComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxChanged()));

    onComboBoxPopup(portComboBox);
}
void VisualSerialNode::onComboBoxPopup(ComboBox* combobox)
{
    loadSerialPorts();
}
void VisualSerialNode::onComboBoxChanged()
{
    activate();
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
    node->closeSerialPort();
    qDebug("%s",portComboBox->currentText().toStdString().c_str());
    node->settings->nodeSettings.name = portComboBox->currentText();
    node->openSerialPort();
}

VisualNodeBase* VisualSerialNode::clone()
{
    return new VisualSerialNode();
}
bool running = false;
void VisualSerialNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing,QPainter::TextAntialiasing);
    if(running)
    {
        height = 50;
    }
    else {
        height = 100;
    }
    paintBase(painter,this,"Serial");
    drawConnectors(painter, this);
    drawStartStop(painter,running);
}
void VisualSerialNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(startStopClicked(event->pos()))
    {
        running = !running;
    }
    else {
        VisualSourceNodeBase::mousePressEvent(event);
    }
}
void VisualSerialNode::loadSerialPorts()
{
    portComboBox->clear();
    portComboBox->addItem("");
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        portComboBox->addItem(info.portName());
    }
}
