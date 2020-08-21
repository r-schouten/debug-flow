#pragma once

#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include "propertywidgetbase.h"
#include "testgeneratorsettings.h"

class TestGeneratorPropertiesWidget : public PropertyWidgetBase
{
    Q_OBJECT
public:
    TestGeneratorPropertiesWidget(QWidget *parent, DbgLogger *dbgLogger, TestGeneratorSettings *settings);
    virtual ~TestGeneratorPropertiesWidget();

private slots:
    void addTimestampChanged(int state);
    void fromThreadChanged(int state);
    void splitOnLineChanged(int state);

    void updateRateBoxChanged();
    void dataPerUpdateChanged();

    void anySequenceChanged(int state);
    void startStopClicked();
    void notifyFromThreadChanged(int state);
private:
    TestGeneratorSettings* settings = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    QWidget *formContainter = nullptr;
    QFormLayout *formLayout = nullptr;

    QWidget *container = nullptr;
    QVBoxLayout *containerLayout = nullptr;


    QPushButton* startStop = nullptr;

    QCheckBox *addTimestampCheckbox = nullptr;
    QCheckBox *fromThreadCheckbox = nullptr;
    QCheckBox *notifyFromThreadCheckbox = nullptr;

    QCheckBox *splitOnNewLineCheckbox = nullptr;

    QSpinBox *updateRateBox = nullptr;
    QSpinBox *dataPerUpdateBox = nullptr;

    QList<QCheckBox*> sentenceEnabledCheckboxes;
};


