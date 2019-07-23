#include "combobox.h"

ComboBox::ComboBox()
{

}

void ComboBox::showPopup()
{
    emit onShowPopup(this);
    QComboBox::showPopup();
}
