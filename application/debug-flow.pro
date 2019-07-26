QT += widgets serialport
QT += testlib
requires(qtConfig(combobox))

TARGET = debug-flow
TEMPLATE = app

SOURCES += \
    circularbuffer/circularbuffer.cpp \
    circularbuffer/circularbufferreader.cpp \
    main.cpp \
    mainwindow.cpp \
    nodes/inputnode.cpp \
    nodes/nodebase.cpp \
    nodes/nodesettingsbase.cpp \
    nodes/output_nodes/filteredconsole.cpp \
    nodes/output_nodes/simpleconsole.cpp \
    nodes/outputnode.cpp \
    nodes/processing_nodes/contextfilternode.cpp \
    nodes/source_nodes/serialnode.cpp \
    nodes/source_nodes/serialsettingsbase.cpp \
    nodes/subscription.cpp \
    settingsdialog.cpp \
    test/circularbuffertest.cpp \
    utils/ansiescapereader.cpp \
    utils/contextfilter.cpp \
    utils/utils.cpp \
    visualNodes/connection/connector.cpp \
    visualNodes/connection/visualconnection.cpp \
    visualNodes/outputNodes/visualfilteredconsole.cpp \
    visualNodes/outputNodes/visualoutputnodebase.cpp \
    visualNodes/outputNodes/visualsimpleconsole.cpp \
    visualNodes/prossesing_nodes/visualcontextfilter.cpp \
    visualNodes/resourceList/itemlist.cpp \
    visualNodes/resourceList/mytreewidgetitem.cpp \
    visualNodes/scene/graphicsview.cpp \
    visualNodes/scene/nodescene.cpp \
    visualNodes/selectionmanager.cpp \
    visualNodes/source_nodes/visualserialnode.cpp \
    visualNodes/source_nodes/visualsourcenodebase.cpp \
    visualNodes/visualnodebase.cpp \
    widgets/combobox.cpp \
    windows/dialogwindow.cpp \
    windows/mdiwindow.cpp \
    windows/windowbase.cpp \
    windows/windowmanager.cpp

HEADERS += \
    circularbuffer/circularbuffer.h \
    circularbuffer/circularbufferreader.h \
    main.h \
    mainwindow.h \
    nodes/inputnode.h \
    nodes/nodebase.h \
    nodes/nodesettingsbase.h \
    nodes/output_nodes/filteredconsole.h \
    nodes/output_nodes/simpleconsole.h \
    nodes/outputnode.h \
    nodes/processing_nodes/contextfilternode.h \
    nodes/source_nodes/serialnode.h \
    nodes/source_nodes/serialsettingsbase.h \
    nodes/subscription.h \
    settingsdialog.h \
    test/circularbuffertest.h \
    utils/ansi_types.h \
    utils/ansiescapereader.h \
    utils/contextfilter.h \
    utils/utils.h \
    visualNodes/connection/connectionstyle.h \
    visualNodes/connection/connector.h \
    visualNodes/connection/visualconnection.h \
    visualNodes/nodestylebase.h \
    visualNodes/outputNodes/outputstyle.h \
    visualNodes/outputNodes/visualfilteredconsole.h \
    visualNodes/outputNodes/visualoutputnodebase.h \
    visualNodes/outputNodes/visualsimpleconsole.h \
    visualNodes/prossesing_nodes/processingstyle.h \
    visualNodes/prossesing_nodes/visualcontextfilter.h \
    visualNodes/resourceList/itemlist.h \
    visualNodes/resourceList/mytreewidgetitem.h \
    visualNodes/scene/graphicsview.h \
    visualNodes/scene/nodescene.h \
    visualNodes/selectionmanager.h \
    visualNodes/source_nodes/sourcestyle.h \
    visualNodes/source_nodes/visualserialnode.h \
    visualNodes/source_nodes/visualsourcenodebase.h \
    visualNodes/visualnodebase.h \
    visualNodes/visualnodeconfig.h \
    widgets/combobox.h \
    windows/dialogwindow.h \
    windows/mdiwindow.h \
    windows/windowbase.h \
    ui_mainwindow.h \
    windows/windowmanager.h

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
    visualNodes/outputNodes \
    nodes/processing_nodes \
    nodes/source_nodes \
    nodes/output_nodes \
    utils \
    widgets
target.path = C:/debug-flow/builds
INSTALLS += target
