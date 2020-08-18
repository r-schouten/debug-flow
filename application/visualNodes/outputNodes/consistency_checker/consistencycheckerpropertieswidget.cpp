#include "consistencycheckerpropertieswidget.h"

ConsistencyCheckerPropertiesWidget::ConsistencyCheckerPropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, ConsistencyCheckerSettings* settings)
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

    showAll = new QCheckBox("show all");
    showAll->setChecked(settings->getShowAll());
    containerLayout->addWidget(showAll);

    historicalUpdateButton = new QPushButton("historical update");
    containerLayout->addWidget(historicalUpdateButton);

    connect(showAll,SIGNAL(stateChanged(int)),this,SLOT(showAllChanged(int)));
    connect(historicalUpdateButton,SIGNAL(clicked(bool)),this,SLOT(historicalUpdateClicked(bool)));

}
ConsistencyCheckerPropertiesWidget::~ConsistencyCheckerPropertiesWidget()
{

}
void ConsistencyCheckerPropertiesWidget::showAllChanged(int )
{
    settings->setShowAll(showAll->isChecked());
}
void ConsistencyCheckerPropertiesWidget::historicalUpdateClicked(bool)
{
    settings->notifySettingsChanged(DATA_INVALID, DONT_SAVE, PROPERIES,0);
}
