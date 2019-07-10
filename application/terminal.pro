QT += widgets serialport
QT += testlib
requires(qtConfig(combobox))

TARGET = terminal
TEMPLATE = app

SOURCES += \
    circularbuffer/circularbuffer.cpp \
    circularbuffer/circularbufferreader.cpp \
    filteredconsole.cpp \
    main.cpp \
    mainwindow.cpp \
    nodes/inputnode.cpp \
    nodes/nodebase.cpp \
    nodes/outputnode.cpp \
    settingsdialog.cpp \
    tagfilter.cpp \
    test/circularbuffertest.cpp

HEADERS += \
    circularbuffer/circularbuffer.h \
    circularbuffer/circularbufferreader.h \
    filteredconsole.h \
    main.h \
    mainwindow.h \
    nodes/inputnode.h \
    nodes/nodebase.h \
    nodes/outputnode.h \
    settingsdialog.h \
    tagfilter.h \
    test/circularbuffertest.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc
INCLUDEPATH += \
    circularbuffer \
    nodes
target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target
