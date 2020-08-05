#include "testgeneratorpropertieswidget.h"

TestGeneratorPropertiesWidget::TestGeneratorPropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, TestGeneratorSettings* settings)
    :PropertyWidgetBase(parent, dbgLogger), settings(settings)
{
    //main layout
    mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setMargin(10);
    mainLayout->setAlignment(Qt::AlignTop);
    this->setLayout(mainLayout);

    //container layout, inside the mainlayout
    container = new QWidget();
    containerLayout = new QVBoxLayout;
    containerLayout->setMargin(0);
    container->setLayout(containerLayout);
    mainLayout->addWidget(container);

    //form layout, inside the mainlayout
    formContainter = new QWidget();
    formLayout = new QFormLayout;
    formLayout->setMargin(0);
    formContainter->setLayout(formLayout);
    mainLayout->addWidget(formContainter);

    updateRateBox = new QSpinBox();
    updateRateBox->setRange(10,10000);
    updateRateBox->setValue(settings->getUpdateRate());
    updateRateBox->setSuffix("ms");
    updateRateBox->setSingleStep(10);
    formLayout->addRow("update rate",updateRateBox);
    connect(updateRateBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &TestGeneratorPropertiesWidget::updateRateBoxChanged);

    dataPerUpdateBox = new QSpinBox();
    dataPerUpdateBox->setRange(50,10000);
    dataPerUpdateBox->setValue(settings->getDataPerUpdate());
    dataPerUpdateBox->setSingleStep(10);
    dataPerUpdateBox->setSuffix("bytes");
    formLayout->addRow("data per update",dataPerUpdateBox);
    connect(dataPerUpdateBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &TestGeneratorPropertiesWidget::dataPerUpdateChanged);

    //buttons
    startStop  = new QPushButton();
    if(settings->getEnabled()){
        startStop->setText("stop");
    }
    else{
        startStop->setText("start");
    }
    containerLayout->addWidget(startStop);
    connect(startStop, SIGNAL(clicked()), this, SLOT(startStopClicked()));

    //on containerlayout
    addTimestampCheckbox = new QCheckBox("add timestamp");
    addTimestampCheckbox->setChecked(settings->getAddTimestamp());
    containerLayout->addWidget(addTimestampCheckbox);
    connect(addTimestampCheckbox, SIGNAL(stateChanged(int)), this, SLOT(addTimestampChanged(int)));

    fromThreadCheckbox = new QCheckBox("from thread");
    fromThreadCheckbox->setChecked(settings->getFromThread());
    containerLayout->addWidget(fromThreadCheckbox);
    connect(fromThreadCheckbox, SIGNAL(stateChanged(int)), this, SLOT(fromThreadChanged(int)));

    splitOnNewLineCheckbox = new QCheckBox("split on newline");
    splitOnNewLineCheckbox->setChecked(settings->getSplitOnNewLine());
    containerLayout->addWidget(splitOnNewLineCheckbox);
    connect(splitOnNewLineCheckbox, SIGNAL(stateChanged(int)), this, SLOT(splitOnLineChanged(int)));

    //generators
    QLabel* label = new QLabel("enable generators");
    containerLayout->addWidget(label);

    for(int i = 0; i < settings->getAmountOfSenteces();i++)
    {
        QCheckBox* checkbox = new QCheckBox(settings->getSentenceName((Sentence)i));
        checkbox->setChecked(settings->getSentenceEnabled((Sentence)i));
        containerLayout->addWidget(checkbox);
        sentenceEnabledCheckboxes.append(checkbox);
        connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(anySequenceChanged(int)));
    }



}

TestGeneratorPropertiesWidget::~TestGeneratorPropertiesWidget()
{

}
void TestGeneratorPropertiesWidget::startStopClicked()
{
    bool enabled = !settings->getEnabled();
    settings->setEnabled(enabled);
    if(enabled)
    {
        startStop->setText("stop");
    }
    else
    {
        startStop->setText("start");
    }
}
void TestGeneratorPropertiesWidget::addTimestampChanged(int state)
{
    settings->setAddTimestamp(state);
}
void TestGeneratorPropertiesWidget::fromThreadChanged(int state)
{
    settings->setFromThread(state);
}
void TestGeneratorPropertiesWidget::splitOnLineChanged(int state)
{
    settings->setSplitOnNewLine(state);
}
void TestGeneratorPropertiesWidget::anySequenceChanged(int state)
{
    for(int i=0;i<settings->getAmountOfSenteces();i++)
    {
        settings->setSentenceEnabled(sentenceEnabledCheckboxes[i]->isChecked(), (Sentence)i);
    }
}
void TestGeneratorPropertiesWidget::updateRateBoxChanged()
{
    settings->setUpdateRate(updateRateBox->value());
}
void TestGeneratorPropertiesWidget::dataPerUpdateChanged()
{
    settings->setDataPerUpdate(dataPerUpdateBox->value());
}

