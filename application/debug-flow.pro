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
    utils/utils.cpp \
    visualNodes/connection/connector.cpp \
    visualNodes/connection/visualconnection.cpp \
    visualNodes/prossesing_nodes/visualcontextfilter.cpp \
    visualNodes/resourceList/itemlist.cpp \
    visualNodes/resourceList/mytreewidgetitem.cpp \
    visualNodes/scene/graphicsview.cpp \
    visualNodes/scene/nodescene.cpp \
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
    utils/utils.h \
    visualNodes/connection/connector.h \
    visualNodes/connection/visualconnection.h \
    visualNodes/nodestylebase.h \
    visualNodes/prossesing_nodes/processingstyle.h \
    visualNodes/prossesing_nodes/visualcontextfilter.h \
    visualNodes/resourceList/itemlist.h \
    visualNodes/resourceList/mytreewidgetitem.h \
    visualNodes/scene/graphicsview.h \
    visualNodes/scene/nodescene.h \
    visualNodes/source_nodes/sourcestyle.h \
    visualNodes/source_nodes/visualserialnode.h \
    visualNodes/visualnodebase.h \
    windows/dialogwindow.h \
    windows/mdiwindow.h \
    windows/windowbase.h \
    ui_mainwindow.h

FORMS += \
    mainwindow_old.ui \
    settingsdialog.ui \
    testwindow.ui

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
    visualNodes/resourceList \
    visualNodes/connection \
    nodes/processing_nodes \
    nodes/source_nodes \
    utils
target.path = C:/debug-flow/builds
INSTALLS += target
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O3
QMAKE_CXXFLAGS_RELEASE -= -Os
QMAKE_CXXFLAGS_RELEASE += -Og
