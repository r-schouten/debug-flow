#pragma once
#include <QFormLayout>
#include <QWidget>

class PropertyWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidgetBase(QWidget *parent);
    virtual ~PropertyWidgetBase();
protected:
    QFormLayout *layout = nullptr;
};

