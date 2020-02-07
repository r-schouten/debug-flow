#pragma once
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

#include "nodesettingsbase.h"
#include "filtertag.h"

#include "json_defs.h"

#define DEFAULT_CONSOLE_BLOCK_COUNT 10000

//waring, when changing to enum also change the serialization an deserialisation
static QStringList ScrollOptionsText = {"scrollbar","ignore","newline"};
enum class HorizontalScrollOptions:int{
    scrollbar=0,
    ignore=1,
    newline=2
};

class FilteredNodeSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    QList<Tag*> tags;
    bool LineNumbersEnabled = false;
    bool ANSIEnabled = true;
    bool autoScrollEnabled = true;
    bool hideContext = false;

    FilteredNodeSettings();

    void addOption(Tag* tag,TagOption* option);
    void setHorizontalScroll(const HorizontalScrollOptions &value);
    HorizontalScrollOptions getHorizontalScroll() const;
    int getMaxLines() const;
    void setMaxLinesComboBox(int value);

    bool getFilterOnWindow() const;
    void setFilterOnWindow(bool value);

    QJsonObject *serialize(SerializationHandler &handler);
    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
private:
    int maxLines = DEFAULT_CONSOLE_BLOCK_COUNT;
    HorizontalScrollOptions horizontalScroll = HorizontalScrollOptions::scrollbar;
    bool filterOnWindow = true;

signals:
    void optionAdded(Tag* tag,TagOption* option);
    void clearConsole();
    void tagsChanged();
    void maxLinesChanged();
    void scrollSettingsChanged();
    void filterOnWindowChanged();
public slots:
    void clearConsoleClicked();
    void clearContextClicked();
};

