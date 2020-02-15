#pragma once
#include <QEvent>
#include <QScrollArea>
#include <QWidget>
#include <QListWidget>

#include "commandbase.h"

class FlowData;
class LoadStore;
class UndoRedoManager: public QObject
{
    Q_OBJECT
private:
    int eventCounter = 0;

    QListWidget *undoView;
    QList<CommandBase*> undoStack;
    int cursorPosition = 0;
    FlowData* flowData = nullptr;
    LoadStore* loadStore = nullptr;

public:
    UndoRedoManager(QScrollArea *scrollArea);
    ~UndoRedoManager();
    void setData(FlowData* _flowData, LoadStore* _loadStore);

    void registerEvent();
    void pushChange(CommandBase *command);
    void undo();
    void redo();
};

