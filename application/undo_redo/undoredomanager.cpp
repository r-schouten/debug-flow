#include "undoredomanager.h"

UndoRedoManager* UndoRedoManager::undoRedoManager;

UndoRedoManager::UndoRedoManager()
{

}
void UndoRedoManager::setData(QScrollArea *scrollArea, NodeScene *_scene, LoadStore *_loadStore)
{
    nodeScene = _scene;
    loadStore = _loadStore;
    undoView = new QUndoView(&undoStack);
    scrollArea->setWidget(undoView);
}

UndoRedoManager* UndoRedoManager::get()
{
    if(undoRedoManager == nullptr)
    {
        undoRedoManager = new UndoRedoManager();
    }
    return undoRedoManager;
}

void UndoRedoManager::registerEvent(QEvent &event)
{
    eventCounter++;
    qDebug("[debug][MementoManager] event happended %d eventcounter = %d", event.type(), eventCounter);

}

void UndoRedoManager::pushChange(CommandBase *command)
{
    command->setUtils(nodeScene, loadStore);

    undoStack.push(command);
}

void UndoRedoManager::undo()
{
    if(undoStack.canUndo())
    {
        undoStack.undo();
    }
}

void UndoRedoManager::redo()
{
    if(undoStack.canRedo())
    {
        undoStack.redo();
    }
}
