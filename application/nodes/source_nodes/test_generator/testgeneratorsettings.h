#pragma once

#include <QJsonObject>

#include "nodesettingsbase.h"

#define AMOUNT_OF_SENTENCES 13


enum Sentence
{
    VALUE = 0,
    VALUE2 = 1,
    FLOATVAlUE = 2,
    CONTEXT_X2 = 3,
    CONTEXT_X2_2 = 4,
    MUCH_CONTEXT = 5,
    RANDOM_CONTEXT = 6,
    LONG_SENTENCE = 7,
    ANSII1 = 8,
    ANSII_IN_CONTEXT = 9,
    GARBAGE1 = 10,
    GARBAGE2 = 11,
    GARBAGE3 = 12,
};

class TestGeneratorSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    TestGeneratorSettings(DbgLogger* dbgLogger);

    QJsonObject *serialize(SerializationHandler &handler);

    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    void notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event);

    bool getAddTimestamp() const;
    void setAddTimestamp(bool value);

    bool getFromThread() const;
    void setFromThread(bool value);

    bool getSplitOnNewLine() const;
    void setSplitOnNewLine(bool value);

    bool getSentenceEnabled(Sentence index) const;
    void setSentenceEnabled(bool value, Sentence index);
    QString getSentenceName(Sentence index);

    int getAmountOfSenteces() const;

    int getUpdateRate() const;
    void setUpdateRate(int value);

    int getDataPerUpdate() const;
    void setDataPerUpdate(int value);

    bool getEnabled() const;
    void setEnabled(bool value);

private:
    bool enabled = true;
    bool addTimestamp = true;
    bool fromThread = false;
    bool splitOnNewLine = true;

    const int amountOfSenteces = AMOUNT_OF_SENTENCES;
    bool sentenceEnabled[AMOUNT_OF_SENTENCES];

    int updateRate = 500;
    int dataPerUpdate = 100;

    QStringList sentenceNames = {"value","value2","float value", "2x context", "2x context2",
                               "much context", "random context", "long sentence","ANSII escape", "ANSII in context",
                               "garbage 1","garbage 2", "garbage3"};
signals:
    void updateRateChanged();
};
