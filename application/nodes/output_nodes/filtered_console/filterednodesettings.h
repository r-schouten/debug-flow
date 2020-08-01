#pragma once
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

#include "nodesettingsbase.h"
#include "filtertag.h"
#include "tagandoptionssettings.h"
#include "json_defs.h"

#define DEFAULT_CONSOLE_BLOCK_COUNT 10000

//waring, when changing to enum also change the serialization an deserialisation
static QStringList ScrollOptionsText = {"scrollbar","ignore","newline"};
enum class HorizontalScrollOptions:int{
    scrollbar=0,
    ignore=1,
    newline=2
};
static QStringList SideLineOptionsText = {"none","linenumbers","time", "both"};
enum class SideLineOptions:int{
    NONE=0,
    LINENUMBERS=1,
    TIME=2,
    BOTH=3
};


class FilteredNodeSettings: public NodeSettingsBase
{
    Q_OBJECT
public:
    TagAndOptionsSettings* tagAndOptionSettings = nullptr;
    FilteredNodeSettings(DbgLogger* dbgLogger);
    virtual ~FilteredNodeSettings();
    void setHorizontalScroll(const HorizontalScrollOptions &value);
    HorizontalScrollOptions getHorizontalScroll() const;
    int getMaxLines() const;
    void setMaxLinesComboBox(int value);

    bool getFilterOnWindow() const;
    void setFilterOnWindow(bool value);

    bool getAutoScrollEnabled() const;
    void setAutoScrollEnabled(bool value);

    SideLineOptions getSideLineOptions() const;
    void setSideLineOptions(SideLineOptions value);

    QJsonObject *serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);

    void notifySettingsChanged(DataValid dataValid = DATA_VALID,SaveSettings saveSettings = SAVE, SettingsChangeSource source = PROPERIES, int event = 0);

private:
    int maxLines = DEFAULT_CONSOLE_BLOCK_COUNT;
    HorizontalScrollOptions horizontalScroll = HorizontalScrollOptions::scrollbar;
    bool filterOnWindow = true;

    SideLineOptions sideLineOption = SideLineOptions::NONE;
    bool autoScrollEnabled = true;
signals:
    void clearConsole();

    void maxLinesChanged();
    void scrollSettingsChanged();
    void filterOnWindowChanged();
    void SideLineOptionsChanged();
public slots:
    void clearConsoleClicked();
    void clearContextClicked();

};

