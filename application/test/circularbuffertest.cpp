#include "test/circularbuffertest.h"
#ifdef IS_TESTING

CircularBufferTest::CircularBufferTest()
{

}
QString GetRandomString(int length, bool printableChars)
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i<length; i++)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar;
       if(printableChars)
       {
           nextChar = possibleCharacters.at(index);
       }
       else {
           nextChar = QChar(((char)(i % 250+1)));
       }
       randomString.append(nextChar);
   }
   return randomString;
}
QByteArray getRandomBytes(int length, bool printableChars)
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QByteArray randomString;
   for(int i=0; i<length; i++)
   {
       int index = qrand() % possibleCharacters.length();
       if(printableChars)
       {
           randomString.append(possibleCharacters.at(index));

       }
       else {
           randomString.append(qrand()%255);
       }
   }
   return randomString;
}
bool CircularBufferTest::testContinousAppendRead(CircularBuffer* buffer,int iterations, bool printableChars, bool perByte)
{
    CircularBufferReader* reader = buffer->requestNewReader();
    for(int iteration = 0;iteration<iterations;iteration++)
    {
        QByteArray byteArray = getRandomBytes(qrand() % 200 + 1,printableChars);
        //qDebug("byteArray size %d",byteArray->size());
        if(perByte)
        {
            for(int i=0;i<byteArray.length();i++)
            {
                char byte = byteArray.at(i);
                buffer->appendByte(&byte);
            }
        }
        else
        {
            buffer->append(&byteArray);
        }

        if(reader->availableSize() != byteArray.length())
        {
            qDebug("CircularBufferTest::testContinousAppendRead() : reader->availableSize() != testString.length()");
            qDebug("iteration %d    %d %d",iteration, reader->availableSize(),byteArray.length());
            return false;
        }

        for(int i = 0;i<reader->availableSize();i++)
        {
            if((*reader)[i] != byteArray.at(i))
            {
                qDebug("CircularBufferTest::testContinousAppendRead() : (*reader)[i] != testString.at(i) %c %c  %d %d",(*reader)[i],byteArray.at(i),iteration,i);
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
    CircularBuffer* circularBuffer = new CircularBuffer(DbgLogger::getStaticLogger(),1000,1000);
    QVERIFY(testContinousAppendRead(circularBuffer,1000, true, false));
    //QVERIFY(testContinousAppendRead(circularBuffer,10000, true, false));

    delete circularBuffer;

}
void CircularBufferTest::testContinousAppendReadPerByte()
{
    CircularBuffer* circularBuffer = new CircularBuffer(DbgLogger::getStaticLogger(),1000,1000);
    QVERIFY(testContinousAppendRead(circularBuffer,1000, true, true));
    delete circularBuffer;
}
void CircularBufferTest::testContinousAppendRead2()
{
    CircularBuffer* circularBuffer = new CircularBuffer(DbgLogger::getStaticLogger(),1000,1000);
    QVERIFY(testContinousAppendRead(circularBuffer,1000, false, false));

    delete circularBuffer;

}

void CircularBufferTest::testContinousAppend()
{
    CircularBuffer* circularBuffer = new CircularBuffer(DbgLogger::getStaticLogger(),100,100);
    for(int iteration = 0;iteration<10000;iteration++)
    {
        QString testString = GetRandomString(qrand() % 50,true);
        char* data = const_cast<char*>(testString.toStdString().c_str());
        circularBuffer->append(data,testString.length());
    }
    delete circularBuffer;
    QVERIFY(true);
}

void CircularBufferTest::testContionousRead()
{
    CircularBuffer* circularBuffer = new CircularBuffer(DbgLogger::getStaticLogger(),100,100);
    CircularBufferReader* reader = circularBuffer->requestNewReader();

    QString testString = GetRandomString(qrand() % 50,true);
    char* data = const_cast<char*>(testString.toStdString().c_str());
    circularBuffer->append(data,testString.length());

    for(int iteration = 0;iteration<1000;iteration++)
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
