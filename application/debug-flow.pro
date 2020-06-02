QT += widgets serialport
QT += testlib
requires(qtConfig(combobox))

TARGET = debug-flow
TEMPLATE = app

SOURCES += \
    circularbuffer/circularbuffer.cpp \
    circularbuffer/circularbufferreader.cpp \
    flowdata.cpp \
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
    nodes/output_nodes/filtered_console/filteredconsole.cpp \
    nodes/output_nodes/filtered_console/filteredconsolewidgets.cpp \
    nodes/output_nodes/filtered_console/filterednodesettings.cpp \
    nodes/output_nodes/filtered_console/filtertag.cpp \
    nodes/output_nodes/simpleconsole.cpp \
    nodes/outputnode.cpp \
    nodes/processing_nodes/contextfilternode.cpp \
    nodes/processing_nodes/contextfiltersettings.cpp \
    nodes/source_nodes/serialnode.cpp \
    nodes/source_nodes/serialnodeinterface.cpp \
    nodes/source_nodes/serialsettings.cpp \
    nodes/subscription.cpp \
    test/circularbuffertest.cpp \
    undo_redo/commands/commandbase.cpp \
    undo_redo/commands/createconnectioncommand.cpp \
    undo_redo/commands/createnodecommand.cpp \
    undo_redo/commands/movecommand.cpp \
    undo_redo/undoredomanager.cpp \
    utils/ansiescapereader.cpp \
    utils/contextfilterengine.cpp \
    utils/flowobjects.cpp \
    utils/tagandoptionssettings.cpp \
    utils/utils.cpp \
    visualNodes/components/tagsandoptionswidget.cpp \
    visualNodes/connection/connector.cpp \
    visualNodes/connection/visualconnection.cpp \
    visualNodes/outputNodes/filtered_console/filteredconsolepropertieswidget.cpp \
    visualNodes/outputNodes/filtered_console/visualfilteredconsole.cpp \
    visualNodes/outputNodes/visualoutputnodebase.cpp \
    visualNodes/outputNodes/visualsimpleconsole.cpp \
    visualNodes/propertywidgetbase.cpp \
    visualNodes/propertywidgetmanager.cpp \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilter.cpp \
    visualNodes/prossesing_nodes/visual_context_filter/visualcontextfilterpropertieswidget.cpp \
    visualNodes/resourceList/itemlist.cpp \
    visualNodes/resourceList/mytreewidgetitem.cpp \
    visualNodes/scene/graphicsview.cpp \
    visualNodes/scene/nodescene.cpp \
    visualNodes/selectionmanager.cpp \
    visualNodes/source_nodes/serial_node/serialnodepropertieswidget.cpp \
    visualNodes/source_nodes/serial_node/visualserialnode.cpp \
    visualNodes/source_nodes/visualsourcenodebase.cpp \
    visualNodes/visualnodebase.cpp \
    widgets/combobox.cpp \
    widgets/taggroupbox.cpp \
    windows/dialogwindow.cpp \
    windows/mdiwindow.cpp \
    windows/windowbase.cpp \
    windows/windowmanager.cpp

HEADERS += \
    circularbuffer/circularbuffer.h \
    circularbuffer/circularbufferreader.h \
    flowdata.h \
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
    nodes/output_nodes/filtered_console/filteredconsole.h \
    nodes/output_nodes/filtered_console/filteredconsolewidgets.h \
    nodes/output_nodes/filtered_console/filterednodesettings.h \
    nodes/output_nodes/filtered_console/filtertag.h \
    nodes/output_nodes/simpleconsole.h \
    nodes/outputnode.h \
    nodes/processing_nodes/contextfilternode.h \
    nodes/processing_nodes/contextfiltersettings.h \
    nodes/source_nodes/serialnode.h \
    nodes/source_nodes/serialnodeinterface.h \
    nodes/source_nodes/serialsettings.h \
    nodes/subscription.h \
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
    utils/flowobjects.h \
    utils/tagandoptionssettings.h \
    utils/utils.h \
    visualNodes/components/tagsandoptionswidget.h \
    visualNodes/connection/connectionstyle.h \
    visualNodes/connection/connector.h \
    visualNodes/connection/visualconnection.h \
    visualNodes/nodestylebase.h \
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
    visualNodes/resourceList/itemlist.h \
    visualNodes/resourceList/mytreewidgetitem.h \
    visualNodes/scene/graphicsview.h \
    visualNodes/scene/nodescene.h \
    visualNodes/selectionmanager.h \
    visualNodes/source_nodes/serial_node/serialnodepropertieswidget.h \
    visualNodes/source_nodes/serial_node/visualserialnode.h \
    visualNodes/source_nodes/sourcestyle.h \
    visualNodes/source_nodes/visualsourcenodebase.h \
    visualNodes/visualnodebase.h \
    visualNodes/visualnodeconfig.h \
    widgets/combobox.h \
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
    inputNodes \
    windows \
    visualNodes \
    sourceNodes \
    visualNodes/components \
    visualNodes/source_nodes \
    visualNodes/source_nodes/serial_node \
    visualNodes/scene \
    visualNodes/prossesing_nodes \
    visualNodes/resourceList \
    visualNodes/connection \
    visualNodes/outputNodes \
    visualNodes/outputNodes/filtered_console \
    nodes/processing_nodes \
    nodes/processing_nodes/visual_context_filter \
    nodes/output_nodes/filtered_console \
    nodes/source_nodes \
    nodes/output_nodes \
    utils \
    loadstore \
    undo_redo \
    undo_redo/commands \
    userinterface \
    widgets
target.path = C:/debug-flow/builds
INSTALLS += target
