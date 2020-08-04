#include "nodeinfoviewer.h"

NodeInfoViewer::NodeInfoViewer(QWidget *parent) : QWidget(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setVerticalStretch(1);
    this->setSizePolicy(sizePolicy);

    //general layout
    layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(10);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    //univeral node settings layout
    nodeContainer = new QWidget();
    nodeLayout = new QFormLayout();
    nodeLayout->setMargin(0);
    nodeContainer->setLayout(nodeLayout);
    layout->addWidget(nodeContainer);

    //input node settings layout
    inputNodeContainer = new QWidget();
    inputNodeLayout = new QFormLayout();
    inputNodeLayout->setMargin(0);
    inputNodeContainer->setLayout(inputNodeLayout);
    layout->addWidget(inputNodeContainer);

    //output node settings layout
    outputNodeContainer = new QWidget();
    outputNodeLayout = new QFormLayout();
    outputNodeLayout->setMargin(0);
    outputNodeContainer->setLayout(outputNodeLayout);
    layout->addWidget(outputNodeContainer);

    //univeral
    nodeNameLabel = new QLabel();
    nodeLayout->addRow("node name",nodeNameLabel);

    discriptionLabel = new QLabel();
    nodeLayout->addRow("discription",discriptionLabel);

    uniqueIdLabel = new QLabel();
    nodeLayout->addRow("id",uniqueIdLabel);

    //outputnode
    outputNodeLayout->setSpacing(3);

    bufferCapacity = new QLabel();
    outputNodeLayout->addRow("capacity",bufferCapacity);

    bufferMaxCapacity = new QLabel();
    outputNodeLayout->addRow("max capacity",bufferMaxCapacity);

    historicalCapableLabel = new QLabel();
    outputNodeLayout->addRow("historical capable",historicalCapableLabel);

    headLabel = new QLabel();
    outputNodeLayout->addRow("head",headLabel);

    iterationsLabel = new QLabel();
    outputNodeLayout->addRow("iterations",iterationsLabel);

    minTailLabel = new QLabel();
    outputNodeLayout->addRow("min tail",minTailLabel);

    minTailIterationLabel = new QLabel();
    outputNodeLayout->addRow("min iteration",minTailIterationLabel);


    bufferScene = new CircularBufferVisualisation();
    graphicsView = new QGraphicsView(bufferScene);

    graphicsView->setFixedSize(150, 150);
    graphicsView->fitInView(0, 0, 400, 400, Qt::KeepAspectRatio);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(graphicsView);

    //input node


    //timer
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateLabels()));
    updateTimer->start(30);


}

void NodeInfoViewer::setFlowObjects(FlowObjects *_flowObjects)
{
    flowObjects = _flowObjects;
}

void NodeInfoViewer::nodeSelected(VisualNodeBase *visualnode)
{
    activeNode = visualnode;
    updateLabels();

}
void NodeInfoViewer::updateLabels()
{
    if(activeNode == nullptr)return;
    nodeContainer->setVisible(true);

    NodeBase* node = activeNode->getNode();
    OutputNode* outputNode = dynamic_cast<OutputNode*>(node);
    InputNode* inputNode = dynamic_cast<InputNode*>(node);

    nodeNameLabel->setText(activeNode->name);
    discriptionLabel->setText(activeNode->shortDiscription);
    uniqueIdLabel->setText(QString::number(activeNode->getUniqueId()));

    if(node->hasOutput)
    {
        outputNodeContainer->setVisible(true);

        int capacity = outputNode->circularBuffer->capacity;
        bufferCapacity->setText(QString::number(capacity));

        int maxCapacity = outputNode->circularBuffer->maxCapacity;
        bufferMaxCapacity->setText(QString::number(maxCapacity));

        bool historicalCapable = outputNode->circularBuffer->historicalCapable;
        historicalCapableLabel->setText(QString::number(historicalCapable));

        int head = outputNode->circularBuffer->head;
        headLabel->setText(QString::number(head));

        int iterations = outputNode->circularBuffer->iterations;
        iterationsLabel->setText(QString::number(iterations));

        int minTail = outputNode->circularBuffer->minTail;
        minTailLabel->setText(QString::number(minTail));

        int minIterations = outputNode->circularBuffer->minTailIteration;
        minTailIterationLabel->setText(QString::number(minIterations));

        graphicsView->show();
        bufferScene->updatePie(capacity, head, iterations, minTail, minIterations);
    }
    else
    {
        graphicsView->hide();
        outputNodeContainer->hide();

    }
    if(node->hasInput)
    {
        inputNodeContainer->setVisible(true);
    }
    else
    {
        inputNodeContainer->hide();
    }
}

void NodeInfoViewer::nodeDeselected()
{
    activeNode = nullptr;
    nodeContainer->hide();
    inputNodeContainer->hide();
    outputNodeContainer->hide();
    graphicsView->hide();
}
