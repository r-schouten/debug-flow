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
    test/circularbuffertest.cpp \
    visualNodes/graphicsview.cpp \
    visualNodes/nodescene.cpp \
    visualNodes/visualnodebase.cpp \
    visualNodes/visualserialnode.cpp \
    windows/dialogwindow.cpp \
    windows/mdiwindow.cpp \
    windows/windowbase.cpp

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
    test/circularbuffertest.h \
    visualNodes/graphicsview.h \
    visualNodes/nodescene.h \
    visualNodes/visualnodebase.h \
    visualNodes/visualserialnode.h \
    windows/dialogwindow.h \
    windows/mdiwindow.h \
    windows/windowbase.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    debug-flow.qrc
INCLUDEPATH += \
    circularbuffer \
    nodes \
    inputNodes \
    sourceNodes \
    windows \
    visualNodes
target.path = C:/debug-flow/builds
INSTALLS += target
