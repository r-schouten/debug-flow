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
    nodes/processing_nodes/contextfilter.cpp \
    nodes/source_nodes/serialnode.cpp \
    nodes/subscription.cpp \
    settingsdialog.cpp \
    tagfilter.cpp \
    test/circularbuffertest.cpp \
    visualNodes/nodestylebase.cpp \
    visualNodes/prossesing_nodes/processingstyle.cpp \
    visualNodes/prossesing_nodes/visualcontextfilter.cpp \
    visualNodes/scene/graphicsview.cpp \
    visualNodes/scene/nodescene.cpp \
    visualNodes/source_nodes/sourcestyle.cpp \
    visualNodes/source_nodes/visualserialnode.cpp \
    visualNodes/visualnodebase.cpp \
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
    nodes/processing_nodes/contextfilter.h \
    nodes/source_nodes/serialnode.h \
    nodes/subscription.h \
    settingsdialog.h \
    tagfilter.h \
    test/circularbuffertest.h \
    visualNodes/nodestylebase.h \
    visualNodes/prossesing_nodes/processingstyle.h \
    visualNodes/prossesing_nodes/visualcontextfilter.h \
    visualNodes/scene/graphicsview.h \
    visualNodes/scene/nodescene.h \
    visualNodes/source_nodes/sourcestyle.h \
    visualNodes/source_nodes/visualserialnode.h \
    visualNodes/visualnodebase.h \
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
    windows \
    visualNodes \
    sourceNodes \
    visualNodes/source_nodes \
    visualNodes/scene \
    visualNodes/prossesing_nodes \
    nodes/processing_nodes \
    nodes/source_nodes
target.path = C:/debug-flow/builds
INSTALLS += target
