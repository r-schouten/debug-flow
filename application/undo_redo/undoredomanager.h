#pragma once
#include <QEvent>
#include <QScrollArea>
#include <QUndoStack>
#include <QUndoView>
#include <QWidget>
#include <QAction>

#include "commandbase.h"
//#include "loadstore.h"
//#include "nodescene.h"

class NodeScene;
class LoadStore;
class UndoRedoManager: public QObject
{
    Q_OBJECT
private:
    UndoRedoManager();
    static UndoRedoManager *undoRedoManager;
    int eventCounter = 0;
    QUndoView *undoView;

    NodeScene* nodeScene = nullptr;
    LoadStore* loadStore = nullptr;
public:
    QUndoStack undoStack;

    static UndoRedoManager *get();
    void registerEvent(QEvent& event);
    void pushChange(CommandBase *command);
    void undo();
    void redo();
    void setData(QScrollArea *scrollArea, NodeScene* _scene, LoadStore* _loadStore);
};

