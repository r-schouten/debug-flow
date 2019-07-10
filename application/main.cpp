#include "main.h"
#ifdef IS_TESTING

QTEST_MAIN(CircularBufferTest)

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#endif
