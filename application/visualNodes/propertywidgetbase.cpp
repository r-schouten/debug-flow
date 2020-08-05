#include "propertywidgetbase.h"

PropertyWidgetBase::PropertyWidgetBase(QWidget *parent, DbgLogger *dbgLogger) : QWidget (parent), dbgLogger(dbgLogger)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setVerticalStretch(1);
    this->setSizePolicy(sizePolicy);
}

PropertyWidgetBase::~PropertyWidgetBase()
{

}
