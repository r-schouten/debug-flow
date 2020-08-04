#pragma once

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QTimer>

#include <QGraphicsView>
#include "visualnodebase.h"
#include "circularbuffervisualisation.h"
class FlowObjects;
class VisualNodeBase;
class NodeInfoViewer : public QWidget
{
    Q_OBJECT
public:
    explicit NodeInfoViewer(QWidget *parent = nullptr);
    void setFlowObjects(FlowObjects* _flowObjects);

    void nodeSelected(VisualNodeBase* Visualnode);
    void nodeDeselected();
private slots:
    void updateLabels();
private:
    FlowObjects* flowObjects = nullptr;
    VisualNodeBase* activeNode = nullptr;

    QVBoxLayout* layout = nullptr;

    QWidget* nodeContainer = nullptr;
    QWidget* inputNodeContainer = nullptr;
    QWidget* outputNodeContainer = nullptr;

    QFormLayout* nodeLayout = nullptr;
    QFormLayout* outputNodeLayout = nullptr;
    QFormLayout* inputNodeLayout = nullptr;

    QLabel *nodeNameLabel = nullptr;
    QLabel *discriptionLabel = nullptr;
    QLabel *uniqueIdLabel = nullptr;

    //outputnode
    QLabel *bufferCapacity = nullptr;
    QLabel *bufferMaxCapacity = nullptr;
    QLabel *headLabel = nullptr;
    QLabel *iterationsLabel = nullptr;
    QLabel *historicalCapableLabel = nullptr;
    QLabel *minTailLabel = nullptr;
    QLabel *minTailIterationLabel = nullptr;

    QGraphicsView* graphicsView = nullptr;
    CircularBufferVisualisation* bufferScene = nullptr;

    QTimer* updateTimer = nullptr;
};

