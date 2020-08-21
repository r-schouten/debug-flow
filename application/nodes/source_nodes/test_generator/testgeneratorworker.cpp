#include "testgeneratorworker.h"

TestGeneratorWorker::TestGeneratorWorker(TestGeneratorSettings *settings, CircularBuffer *circularBuffer, const std::function<void()>& notifyLambda)
    :settings(settings), circularBuffer(circularBuffer), notifyLambda(notifyLambda)
{

}

TestGeneratorWorker::~TestGeneratorWorker()
{

}


bool TestGeneratorWorker::generateData()
{
    bool found = false;
    for(int i=0;i<=settings->getAmountOfSenteces();i++)
    {
        if(settings->getSentenceEnabled((Sentence)generatorIndex) == false)
        {
            generatorIndex++;
            if(generatorIndex > settings->getAmountOfSenteces())
            {
                generatorIndex = 0;
            }
        }
        else
        {
            found = true;
            break;
        }
    }
    if(found == false) return false;

    if(generatorIndex == Sentence::VALUE)
    {
        data.append("[debug, value] value = ").append(QString::number(QRandomGenerator::global()->bounded(1000))).append("\n");
    }
    if(generatorIndex == Sentence::VALUE2)
    {
        data.append("[debug, sensor, value]").append(QString::number(QRandomGenerator::global()->bounded(10000))).append("\n");
    }
    if(generatorIndex == Sentence::FLOATVAlUE)
    {
        data.append("[debug, sensor, value]").append(QString::number(QRandomGenerator::global()->bounded(100.0))).append("\n");
    }
    if(generatorIndex == Sentence::CONTEXT_X2)
    {
        data.append("[debug, test] test\n[debug, value] value = ").append(QString::number(QRandomGenerator::global()->bounded(1000))).append("\n");
    }
    if(generatorIndex == Sentence::CONTEXT_X2_2)
    {
        data.append("[debug, test] test[debug, sensor, value]").append(QString::number(QRandomGenerator::global()->bounded(10000))).append("\n");
    }
    if(generatorIndex == Sentence::MUCH_CONTEXT)
    {
        data.append("[verbose, tag1, tag2, tag3, tag4, tag5, tag6, tag7, tag8, tag9, tag10] test").append("\n");
    }
    if(generatorIndex == Sentence::RANDOM_CONTEXT)
    {
        data.append("[verbose,").append(QString::number(QRandomGenerator::global()->bounded(100))).append("] random").append("\n");
    }
    if(generatorIndex == Sentence::LONG_SENTENCE)
    {
        data.append("[verbose, long_sentence] Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. ").append("\n");
    }
    if(generatorIndex == Sentence::ANSII1)
    {
        data.append("[verbose, ANSII, normal] normal ").append(RED).append("red ").append(BOLDGREEN).append("bold green ").append(RESET).append("reset").append("\n");
    }
    if(generatorIndex == Sentence::ANSII_IN_CONTEXT)
    {
        data.append("[verbose, ANSII, ").append(BOLDCYAN).append("hard]").append(RESET).append("normal ").append(RED).append("red ").append(BOLDGREEN).append("bold green ").append(RESET).append("reset").append("\n");
    }
    if(generatorIndex == Sentence::GARBAGE1)
    {
        data.append(Utils::getRandomBytes(QRandomGenerator::global()->bounded(20,40),true)).append("\n");
    }
    if(generatorIndex == Sentence::GARBAGE2)
    {
        data.append(Utils::getRandomBytes(QRandomGenerator::global()->bounded(20,40),false)).append("\n");
    }
    if(generatorIndex == Sentence::GARBAGE3)
    {
        data.append(Utils::getRandomBytes(QRandomGenerator::global()->bounded(20,100),false)).append("\n");
    }
    if(generatorIndex == Sentence::THREAD_ID)
    {
        data.append("[debug,threadID] ").append(QString::number((uint64_t)thread()->currentThread(),16)).append("\n");
    }
    if(generatorIndex == Sentence::TEST_DATA)
    {
        static int testNr = 0;
        testNr++;
        data.append("[debug, testdata] this should match exactly ").append(QString::number(testNr)).append("\n");
    }

    generatorIndex++;
    return true;
}
void TestGeneratorWorker::process()
{
    if(!settings->getEnabled())return;
    data.reserve(settings->getDataPerUpdate()*1.5);

    while(data.length() < settings->getDataPerUpdate())
    {
        bool succes = generateData();
        if(!succes)return;
    }

    //the current implementation is slow, it could be made better.
    //it is acceptable now because this code doesn't run in a historical update
    int length = data.length();
    if(settings->getSplitOnNewLine())length = settings->getDataPerUpdate();
    for(int i=0;i<length;i++)
    {
        char a = data.at(i);
        if(settings->getAddTimestamp())
        {
            if(a == '[')
            {
                if(!((i !=0)&&(data.at(i-1)=='\033')))
                {
                    metaDataHelper.appendTime(circularBuffer);
                }
            }
        }
        circularBuffer->appendByte(&a);
    }
    if(!settings->getSplitOnNewLine())
    {
        data.clear();
    }
    else
    {
        data.remove(0, length);
    }
    settings->addDataTransferred(length);
    if(settings->getNotifyFromThread())
    {
        notifyLambda();
    }
    else
    {
        emit updateDone();
    }
}
