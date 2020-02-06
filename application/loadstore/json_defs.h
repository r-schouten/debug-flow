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

//filtered console
#define JSON_FILTEREDCONSOLE_ANSIENABLED "ANSIEnabled"
#define JSON_FILTEREDCONSOLE_LINE_NUMBERS_ENABLED "LineNumbersEnabled"
#define JSON_FILTEREDCONSOLE_AUTO_SCROLL "autoScrollEnabled"
#define JSON_FILTEREDCONSOLE_FILTER_ON_WINDOW "filterOnWindow"
#define JSON_FILTEREDCONSOLE_HIDE_CONTEXT "hideContext"
#define JSON_FILTEREDCONSOLE_MAX_LINES "maxlines"
#define JSON_FILTEREDCONSOLE_H_SCROLL "scrollOption"

#define JSON_FILTEREDCONSOLE_TAGS "tags"
#define JSON_FILTEREDCONSOLE_TAG_NAME "name"
#define JSON_FILTEREDCONSOLE_TAG_VISIBLE "visible"
#define JSON_FILTEREDCONSOLE_TAG_INDEX "index"
#define JSON_FILTEREDCONSOLE_OPTIONS "options"
#define JSON_FILTEREDCONSOLE_OPTION_TAGNAME "tagName"
#define JSON_FILTEREDCONSOLE_OPTION_ENABLED "enabled"


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

*/
