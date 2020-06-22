#pragma once
#include <QEvent>
#include <QScrollArea>
#include <QWidget>
#include <QListWidget>

#include "commandbase.h"

class CommandBase;
class FlowObjects;
class LoadStore;
class UndoRedoManager: public QObject
{
    Q_OBJECT
private:
    int eventCounter = 0;

    QListWidget *undoView;
    QList<CommandBase*> undoStack;
    int cursorPosition = 0;
    FlowObjects* flowObjects = nullptr;
    LoadStore* loadStore = nullptr;

public:
    UndoRedoManager(QScrollArea *scrollArea);
    ~UndoRedoManager();
    void setData(FlowObjects *_flowObjects, LoadStore* _loadStore);

    void registerEvent();
    void pushChange(CommandBase *command);
    void undo();
    void redo();
public slots:
    void notifySettingsChanged();
signals:
    void anythingChanged();
};

