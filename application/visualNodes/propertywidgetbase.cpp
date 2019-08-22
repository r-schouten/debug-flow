#include "propertywidgetbase.h"

PropertyWidgetBase::PropertyWidgetBase(QWidget *parent) : QWidget (parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setVerticalStretch(1);
    this->setSizePolicy(sizePolicy);

    layout = new QFormLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(10);
    layout->setAlignment(Qt::AlignTop);
}

PropertyWidgetBase::~PropertyWidgetBase()
{
    delete layout;
}
