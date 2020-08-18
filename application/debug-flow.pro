QT += widgets serialport
QT += testlib
requires(qtConfig(combobox))

CONFIG += c++20
TARGET = debug-flow
TEMPLATE = app

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE *= -O3

SOURCES += \
    circularbuffer/circularbuffer.cpp \
    circularbuffer/circularbufferreader.cpp \
    features/historicalupdatemanager.cpp \
    features/metadatahelper.cpp \
    flowwidget.cpp \
    loadstore/deserialization_handler.cpp \
    loadstore/filesystem.cpp \
    loadstore/loadstore.cpp \
    loadstore/serialization_handler.cpp \
    main.cpp \
    mainwindow.cpp \
    nodes/inputnode.cpp \
    nodes/nodebase.cpp \
    nodes/nodesettingsbase.cpp \
    nodes/output_nodes/consistency_checker/consistencycheckernode.cpp \
    nodes/output_nodes/consistency_checker/consistencycheckersettings.cpp \
    nodes/output_nodes/filtered_console/consolewidget.cpp \
    nodes/output_nodes/filtered_console/filteredconsole.cpp \
    nodes/output_nodes/filtered_console/filterednodesettings.cpp \
    nodes/output_nodes/filtered_console/filtertag.cpp \
    nodes/output_nodes/filtered_console/tag-option-item.cpp \
    nodes/output_nodes/filtered_console/textblockwithmetadata.cpp \
    nodes/output_nodes/simpleconsole.cpp \
    nodes/outputnode.cpp \
    nodes/processing_nodes/contextfilternode.cpp \
    nodes/processing_nodes/contextfiltersettings.cpp \
    nodes/source_nodes/serial_node/serialnode.cpp \
    nodes/source_nodes/serial_node/serialnodeinterface.cpp \
    nodes/source_nodes/serial_node/serialsettings.cpp \
    nodes/source_nodes/test_generator/testgeneratornode.cpp \
    nodes/source_nodes/test_generator/testgeneratorsettings.cpp \
    nodes/source_nodes/test_generator/testgeneratorworker.cpp \
    nodes/subscription.cpp \
    nodes/tamplate/tamplatenode.cpp \
    nodes/tamplate/tamplatenodesettings.cpp \
    test/circularbuffertest.cpp \
    undo_redo/commands/commandbase.cpp \
    undo_redo/commands/createconnectioncommand.cpp \
    undo_redo/commands/createnodecommand.cpp \
    undo_redo/commands/movecommand.cpp \
    undo_redo/undoredomanager.cpp \
    utils/ansiescapereader.cpp \
    utils/contextfilterengine.cpp \
    utils/dbglogger.cpp \
    utils/flowobjects.cpp \
    utils/tagandoptionssettings.cpp \
    utils/utils.cpp \
    visualNodes/components/tagsandoptionswidget.cpp \
    visualNodes/connection/connector.cpp \
    visualNodes/connection/visualconnection.cpp \
    visualNodes/outputNodes/consistency_checker/consistencycheckerpropertieswidget.cpp \
    visualNodes/outputNodes/consistency_checker/visualconsistencychecker.cpp \
    visualNodes/outputNodes/filtered_console/filteredconsolepropertieswidget.cpp \
    visualNodes/outputNodes/filtered_console/visualfilteredconsole.cpp \
    visualNodes/outputNodes/visualoutputnodebase.cpp \
    visualNodes/outputNodes/visualsimpleconsole.cpp \
    visualNodes/propertywidgetbase.cpp \
    visualNodes/propertywidgetmanager.cpp \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilter.cpp \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilterpropertieswidget.cpp \
    visualNodes/prossesing_nodes/visualprocessingnodebase.cpp \
    visualNodes/resourceList/itemlist.cpp \
    visualNodes/resourceList/mytreewidgetitem.cpp \
    visualNodes/scene/graphicsview.cpp \
    visualNodes/scene/nodescene.cpp \
    visualNodes/selectionmanager.cpp \
    visualNodes/source_nodes/serial_node/serialnodepropertieswidget.cpp \
    visualNodes/source_nodes/serial_node/visualserialnode.cpp \
    visualNodes/source_nodes/test_generator/testgeneratorpropertieswidget.cpp \
    visualNodes/source_nodes/test_generator/visualtestgeneratornode.cpp \
    visualNodes/source_nodes/visualsourcenodebase.cpp \
    visualNodes/tamplate/tamplatenodepropertieswidget.cpp \
    visualNodes/tamplate/visualtamplatenode.cpp \
    visualNodes/visualnodebase.cpp \
    widgets/circularbuffervisualisation.cpp \
    widgets/combobox.cpp \
    widgets/nodeinfoviewer.cpp \
    widgets/taggroupbox.cpp \
    windows/dialogwindow.cpp \
    windows/mdiwindow.cpp \
    windows/windowbase.cpp \
    windows/windowmanager.cpp

HEADERS += \
    circularbuffer/circularbuffer.h \
    circularbuffer/circularbufferreader.h \
    features/historicalupdatemanager.h \
    features/metadatahelper.h \
    flowwidget.h \
    globalconfig.h \
    loadstore/deserialistationexception.h \
    loadstore/deserialization_handler.h \
    loadstore/filesystem.h \
    loadstore/json_defs.h \
    loadstore/loadstore.h \
    loadstore/serialistationexception.h \
    loadstore/serializable.h \
    loadstore/serialization_handler.h \
    main.h \
    mainwindow.h \
    nodes/inputnode.h \
    nodes/nodebase.h \
    nodes/nodesettingsbase.h \
    nodes/output_nodes/consistency_checker/consistencycheckernode.h \
    nodes/output_nodes/consistency_checker/consistencycheckersettings.h \
    nodes/output_nodes/filtered_console/consolewidget.h \
    nodes/output_nodes/filtered_console/filteredconsole.h \
    nodes/output_nodes/filtered_console/filterednodesettings.h \
    nodes/output_nodes/filtered_console/filtertag.h \
    nodes/output_nodes/filtered_console/tag-option-item.h \
    nodes/output_nodes/filtered_console/textblockwithmetadata.h \
    nodes/output_nodes/simpleconsole.h \
    nodes/outputnode.h \
    nodes/processing_nodes/contextfilternode.h \
    nodes/processing_nodes/contextfiltersettings.h \
    nodes/source_nodes/serial_node/serialnode.h \
    nodes/source_nodes/serial_node/serialnodeinterface.h \
    nodes/source_nodes/serial_node/serialsettings.h \
    nodes/source_nodes/test_generator/testgeneratornode.h \
    nodes/source_nodes/test_generator/testgeneratorsettings.h \
    nodes/source_nodes/test_generator/testgeneratorworker.h \
    nodes/subscription.h \
    nodes/tamplate/tamplatenode.h \
    nodes/tamplate/tamplatenodesettings.h \
    test/circularbuffertest.h \
    undo_redo/commands/commandbase.h \
    undo_redo/commands/createconnectioncommand.h \
    undo_redo/commands/createnodecommand.h \
    undo_redo/commands/movecommand.h \
    undo_redo/undoredomanager.h \
    userinterface/ui_flow_widget.h \
    userinterface/ui_mainwindow.h \
    utils/ansi_types.h \
    utils/ansiescapereader.h \
    utils/contextfilterengine.h \
    utils/dbglogger.h \
    utils/flowobjects.h \
    utils/tagandoptionssettings.h \
    utils/utils.h \
    visualNodes/components/tagsandoptionswidget.h \
    visualNodes/connection/connectionstyle.h \
    visualNodes/connection/connector.h \
    visualNodes/connection/visualconnection.h \
    visualNodes/nodestylebase.h \
    visualNodes/outputNodes/consistency_checker/consistencycheckerpropertieswidget.h \
    visualNodes/outputNodes/consistency_checker/visualconsistencychecker.h \
    visualNodes/outputNodes/filtered_console/filteredconsolepropertieswidget.h \
    visualNodes/outputNodes/filtered_console/visualfilteredconsole.h \
    visualNodes/outputNodes/outputstyle.h \
    visualNodes/outputNodes/visualoutputnodebase.h \
    visualNodes/outputNodes/visualsimpleconsole.h \
    visualNodes/propertywidgetbase.h \
    visualNodes/propertywidgetmanager.h \
    visualNodes/prossesing_nodes/processingstyle.h \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilter.h \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilterpropertieswidget.h \
    visualNodes/prossesing_nodes/visualprocessingnodebase.h \
    visualNodes/resourceList/itemlist.h \
    visualNodes/resourceList/mytreewidgetitem.h \
    visualNodes/scene/graphicsview.h \
    visualNodes/scene/nodescene.h \
    visualNodes/selectionmanager.h \
    visualNodes/source_nodes/serial_node/serialnodepropertieswidget.h \
    visualNodes/source_nodes/serial_node/visualserialnode.h \
    visualNodes/source_nodes/sourcestyle.h \
    visualNodes/source_nodes/test_generator/testgeneratorpropertieswidget.h \
    visualNodes/source_nodes/test_generator/visualtestgeneratornode.h \
    visualNodes/source_nodes/visualsourcenodebase.h \
    visualNodes/tamplate/tamplatenodepropertieswidget.h \
   visualNodes/tamplate/visualtamplatenode.h \
    visualNodes/visualnodebase.h \
    visualNodes/visualnodeconfig.h \
    widgets/circularbuffervisualisation.h \
    widgets/combobox.h \
    widgets/nodeinfoviewer.h \
    widgets/taggroupbox.h \
    windows/dialogwindow.h \
    windows/mdiwindow.h \
    windows/windowbase.h \
    windows/windowmanager.h

FORMS += \
    settingsdialog.ui \
    testwindow.ui

RESOURCES += \
    debug-flow.qrc
INCLUDEPATH += \
    circularbuffer \
    nodes \
    features \
    inputNodes \
    windows \
    visualNodes \
    sourceNodes \
    visualNodes/components \
    visualNodes/tamplate \
    visualNodes/source_nodes \
    visualNodes/source_nodes/serial_node \
    visualNodes/source_nodes/test_generator \
    visualNodes/scene \
    visualNodes/prossesing_nodes \
    visualNodes/prossesing_nodes/visual_context_filter \
    visualNodes/resourceList \
    visualNodes/connection \
    visualNodes/outputNodes \
    visualNodes/outputNodes/filtered_console \
    visualNodes/outputNodes/consistency_checker \
    nodes/processing_nodes \
    nodes/processing_nodes/visual_context_filter \
    nodes/output_nodes/filtered_console \
    nodes/source_nodes \
    nodes/source_nodes/test_generator \
    nodes/source_nodes/serial_node \
    nodes/output_nodes \
    nodes/output_nodes/consistency_checker \
    nodes/tamplate \
    utils \
    loadstore \
    undo_redo \
    undo_redo/commands \
    userinterface \
    widgets
target.path = C:/debug-flow/builds
INSTALLS += target
