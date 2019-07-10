#include "test/circularbuffertest.h"
#ifdef IS_TESTING

CircularBufferTest::CircularBufferTest()
{

}
QString GetRandomString(int length)
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i<length; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
bool CircularBufferTest::testContinousAppendRead(CircularBuffer* buffer,int iterations, bool qbytearray)
{
    CircularBufferReader* reader = buffer->requestNewReader();
    for(int iteration = 0;iteration<iterations;iteration++)
    {
        QString testString = GetRandomString(qrand() % 50 + 1);
        if(qbytearray)
        {
            QByteArray *byteArray = new QByteArray(testString.toStdString().c_str());
            buffer->append(byteArray);
            delete byteArray;
        }
        else {
            char* data = const_cast<char*>(testString.toStdString().c_str());
            buffer->append(data,testString.length());
        }

//        for(int i = 0;i<reader->availableSize();i++)
//        {
//            std::cout<<(*reader)[i];
//        }
//        std::cout << std::endl;
//        for(int i = 0;i<testString.length();i++)
//        {
//            std::cout << testString.at(i).toLatin1();
//        }std::cout << std::endl;
//        std::cout <<std::flush;
        if(reader->availableSize() != testString.length())
        {
            qDebug("CircularBufferTest::testContinousAppendRead() : reader->availableSize() != testString.length()");
            qDebug("iteration %d    %d %d",iteration, reader->availableSize(),testString.length());
            return false;
        }

        for(int i = 0;i<reader->availableSize();i++)
        {
            if((*reader)[i] != testString.at(i))
            {
                qDebug("CircularBufferTest::testContinousAppendRead() : (*reader)[i] != testString.at(i)");
                return false;
            }
        }
        reader->release(reader->availableSize());
        if(reader->availableSize() !=0)
        {
            qDebug("CircularBufferTest::testContinousAppendRead() : reader->availableSize() !=0 at iteration %d size %d",iteration,reader->availableSize());
            return false;
        }
    }
    delete reader;

}
void CircularBufferTest::testContinousAppendRead()
{
    CircularBuffer* circularBuffer = new CircularBuffer(100,100);
    QVERIFY(testContinousAppendRead(circularBuffer,1000, true));

    delete circularBuffer;

}
void CircularBufferTest::testContinousAppendRead2()
{
    CircularBuffer* circularBuffer = new CircularBuffer(1000,1000);
    QVERIFY(testContinousAppendRead(circularBuffer,1000, false));

    delete circularBuffer;

}

void CircularBufferTest::testContinousAppend()
{
    CircularBuffer* circularBuffer = new CircularBuffer(100,100);
    for(int iteration = 0;iteration<100;iteration++)
    {
        QString testString = GetRandomString(qrand() % 50);
        char* data = const_cast<char*>(testString.toStdString().c_str());
        circularBuffer->append(data,testString.length());
    }
    delete circularBuffer;
    QVERIFY(true);
}

void CircularBufferTest::testContionousRead()
{
    CircularBuffer* circularBuffer = new CircularBuffer(100,100);
    CircularBufferReader* reader = circularBuffer->requestNewReader();

    QString testString = GetRandomString(qrand() % 50);
    char* data = const_cast<char*>(testString.toStdString().c_str());
    circularBuffer->append(data,testString.length());

    for(int iteration = 0;iteration<100;iteration++)
    {
        int releaseLength = std::min(reader->availableSize(),qrand() % 10);
        int oldLenght = reader->availableSize();
        reader->release(releaseLength );
        if(oldLenght - releaseLength != reader->availableSize())
        {
            QVERIFY(false);
        }
    }
    delete circularBuffer;
    QVERIFY(true);
}
#endif
