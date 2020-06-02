#pragma once

//general keys about nodes
#define JSON_NODES "nodes"
#define JSON_BASE "base"
#define JSON_CONNECTIONS "connections"
#define JSON_DERIVED "derived"
#define JSON_NODE_SETTINGS "settings"

//base keys
#define JSON_BASE_CENTERX "centerX"
#define JSON_BASE_CENTERY "centerY"
#define JSON_BASE_NAME "name"
#define JSON_NODE_TYPE "type"
#define JSON_BASE_UNIQUE_ID "UID"

// connections
#define JSON_CONNECTION_CONNECTOR1_NODE_ID "connector1NodeId"
#define JSON_CONNECTION_CONNECTOR2_NODE_ID "connector2NodeId"
#define JSON_CONNECTION_CONNECTOR1_NAME "connector1Name"
#define JSON_CONNECTION_CONNECTOR2_NAME "connector2Name"
#define JSON_CONNECTION_UNIQUE_ID "UID"
//filtered console
#define JSON_FILTEREDCONSOLE_ANSIENABLED "ANSIEnabled"
#define JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED "LineNumbersEnabled"
#define JSON_FILTEREDCONSOLE_AUTO_SCROLL "autoScrollEnabled"
#define JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW "filterOnWindow"
#define JSON_FILTEREDCONSOLE_MAX_LINES "maxlines"
#define JSON_FILTEREDCONSOLE_H_SCROLL "scrollOption"

#define JSON_FILTEREDCONSOLE_TAG_NAME "name"
#define JSON_FILTEREDCONSOLE_TAG_VISIBLE "visible"
#define JSON_FILTEREDCONSOLE_TAG_INDEX "index"
#define JSON_FILTEREDCONSOLE_OPTIONS "options"
#define JSON_FILTEREDCONSOLE_OPTION_TAGNAME "tagName"
#define JSON_FILTEREDCONSOLE_OPTION_ENABLED "enabled"

#define JSON_SERIAL_RUNNING "running"
#define JSON_SERIAL_NAME "name"
#define JSON_SERIAL_BAUDRATE "baudrate"
#define JSON_SERIAL_DATABITS "databits"
#define JSON_SERIAL_PARITY "parity"
#define JSON_SERIAL_STOPBITS "stopbits"
#define JSON_SERIAL_FLOWCONTROL "flowcontrol"

#define JSON_TAGS "tags"
#define JSON_TAGS_HIDE_CONTEXT "hideContext"

/*
{
    "nodes": [
        {
            "base": {
                "centerX": 169,
                "centerY": 109,
                "name": "filtered console"
            },
            "connections": "nullptr",
            "derived": {
                "type": "VisualFilteredConsole"
            },
            "settings": {
                "ANSIEnabled": false,
                "LineNumbersEnabled": true,
                "autoScrollEnabled": false,
                "filterOnWindow": false,
                "hideContext": true,
                "maxlines": 10000,
                "scrollOption": "scrollbar",
                "tags": [
                ]
            }
        }
    ]
}

{
    "type": "VisualFilteredConsole"
}

test1: verander de naam van "nodes"
test2: verander de naam van "derived" en "base"

*/
