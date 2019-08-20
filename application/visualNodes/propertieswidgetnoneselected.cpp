#include "propertieswidgetnoneselected.h"

#include <QLabel>
#include <QPushButton>

PropertiesWidgetNoneSelected::PropertiesWidgetNoneSelected(QWidget *parent) : QWidget(parent)
{
    QLabel* label = new QLabel(this);
    label->setWordWrap(true);
    label->setMargin(5);
    label->setText("select a node to edit the properties");
    label->show();

    this->show();
}
