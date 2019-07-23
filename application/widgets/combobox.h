#pragma once
#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox();
    void showPopup();
signals:
    void onShowPopup(ComboBox* combobox);
};

