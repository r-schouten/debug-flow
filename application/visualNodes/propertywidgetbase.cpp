#include "propertywidgetbase.h"

PropertyWidgetBase::PropertyWidgetBase(QWidget *parent) : QWidget (parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);

    layout = new QFormLayout;
    layout->setMargin(10);
}

PropertyWidgetBase::~PropertyWidgetBase()
{
    delete layout;
}
