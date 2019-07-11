QT += widgets serialport
QT += testlib
requires(qtConfig(combobox))

TARGET = debug-flow
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
    nodes/subscription.cpp \
    settingsdialog.cpp \
    sourceNodes/serialnode.cpp \
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
    nodes/subscription.h \
    settingsdialog.h \
    sourceNodes/serialnode.h \
    tagfilter.h \
    test/circularbuffertest.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    debug-flow.qrc
INCLUDEPATH += \
    circularbuffer \
    nodes \
    inputNodes \
    sourceNodes
target.path = C:/debug-flow/builds
INSTALLS += target
