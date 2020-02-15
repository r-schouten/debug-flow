#include "undoredomanager.h"

UndoRedoManager::UndoRedoManager(QScrollArea *scrollArea)
{
    undoView = new QListWidget;
    scrollArea->setWidget(undoView);
}


UndoRedoManager::~UndoRedoManager()
{
    undoStack.clear();
    delete undoView;
}

void UndoRedoManager::setData(FlowData *_flowData, LoadStore *_loadStore)
{
    flowData = _flowData;
    loadStore = _loadStore;
}

void UndoRedoManager::registerEvent()
{
    eventCounter++;
    //qDebug("[debug][MementoManager] event happended %d eventcounter = %d", event.type(), eventCounter);
}

void UndoRedoManager::pushChange(CommandBase *command)
{
    while(cursorPosition < undoStack.size())
    {
        CommandBase *undoneCommand = undoStack.takeLast();
        undoView->removeItemWidget(undoneCommand);
        delete undoneCommand;
    }
    command->setId(eventCounter);
    undoStack.insert(cursorPosition, command);
    undoView->insertItem(cursorPosition, command);
    undoView->setCurrentRow(cursorPosition);
    cursorPosition++;
}

void UndoRedoManager::undo()
{
    //loop because there can be multiple entities with the same id
    while(cursorPosition > 0)
    {
        //lower the cursor
        cursorPosition--;

        //take and undo
        CommandBase *undoneCommand = undoStack.at(cursorPosition);

        undoneCommand->undo(flowData,loadStore);

        //insert it above the cursor
        undoView->setCurrentRow(cursorPosition);

        //check if the id is the same
        if(cursorPosition == 0)
        {
            break;
        }
        if(undoStack.at(cursorPosition-1)->getId() != undoneCommand->getId())
        {
            break;
        }
    }
}

void UndoRedoManager::redo()
{
    while(cursorPosition < undoStack.size())
    {
        CommandBase *redoCommand = undoStack.at(cursorPosition);

        redoCommand->undo(flowData,loadStore);

        undoView->setCurrentRow(cursorPosition);

        cursorPosition++;

        if(cursorPosition == undoStack.size())
        {
            break;
        }
        if(undoStack.at(cursorPosition)->getId() != redoCommand->getId())
        {
            break;
        }
    }
}
