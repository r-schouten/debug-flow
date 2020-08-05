#include "testgeneratorsettings.h"

TestGeneratorSettings::TestGeneratorSettings(DbgLogger *dbgLogger)
    :NodeSettingsBase(dbgLogger)
{
    for(int i=0; i< AMOUNT_OF_SENTENCES;i++)
    {
        sentenceEnabled[i] = false;
    }
    setSentenceEnabled(true, Sentence::VALUE);
}

QJsonObject *TestGeneratorSettings::serialize(SerializationHandler &handler)
{
    QJsonObject *jsonObject = new QJsonObject();

    return jsonObject;
}

void TestGeneratorSettings::deserialize(QJsonObject &jsonObject, DeserializationHandler &handler)
{

}

void TestGeneratorSettings::notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event)
{
    Q_UNUSED(dataValid);
    Q_UNUSED(source);
    Q_UNUSED(event);
    dbgLogger->debug(CLASSNAME, __FUNCTION__,"test generator settings changed");
    if(saveSettings == SAVE)
    {
        emit saveAbleChangeOccured();
    }
}

bool TestGeneratorSettings::getAddTimestamp() const
{
    return addTimestamp;
}

void TestGeneratorSettings::setAddTimestamp(bool value)
{
    addTimestamp = value;
}

bool TestGeneratorSettings::getFromThread() const
{
    return fromThread;
}

void TestGeneratorSettings::setFromThread(bool value)
{
    fromThread = value;
}

bool TestGeneratorSettings::getSplitOnNewLine() const
{
    return splitOnNewLine;
}

void TestGeneratorSettings::setSplitOnNewLine(bool value)
{
    splitOnNewLine = value;
}

bool TestGeneratorSettings::getSentenceEnabled(Sentence index) const
{
    return sentenceEnabled[index];
}

void TestGeneratorSettings::setSentenceEnabled(bool value, Sentence index)
{
    sentenceEnabled[index] = value;
}

QString TestGeneratorSettings::getSentenceName(Sentence index)
{
    return sentenceNames.at(index);
}

int TestGeneratorSettings::getAmountOfSenteces() const
{
    return amountOfSenteces;
}

int TestGeneratorSettings::getUpdateRate() const
{
    return updateRate;
}

void TestGeneratorSettings::setUpdateRate(int value)
{
    updateRate = value;
    emit updateRateChanged();
}

int TestGeneratorSettings::getDataPerUpdate() const
{
    return dataPerUpdate;
}

void TestGeneratorSettings::setDataPerUpdate(int value)
{
    dataPerUpdate = value;
}

bool TestGeneratorSettings::getEnabled() const
{
    return enabled;
}

void TestGeneratorSettings::setEnabled(bool value)
{
    enabled = value;
}

uint64_t TestGeneratorSettings::getDataTransferred() const
{
    return dataTransferred;
}

void TestGeneratorSettings::addDataTransferred(const uint32_t &value)
{
    dataTransferred += value;
}
