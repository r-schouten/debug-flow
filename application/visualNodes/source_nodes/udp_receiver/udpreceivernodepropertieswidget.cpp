#include "udpreceivernodepropertieswidget.h"

UdpReceiverNodePropertiesWidget::UdpReceiverNodePropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, UdpReceiverSettings* settings)
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


    //buttons
    startStop  = new QPushButton();
    containerLayout->addWidget(startStop);
    connect(startStop, SIGNAL(clicked()), this, SLOT(startStopClicked()));


}

UdpReceiverNodePropertiesWidget::~UdpReceiverNodePropertiesWidget()
{

}
void UdpReceiverNodePropertiesWidget::startStopClicked()
{
    settings->setEnabled(!settings->getEnabled());
}
