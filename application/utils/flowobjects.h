#pragma once

#include "selectionmanager.h"
#include "undoredomanager.h"

class SelectionManager;
class FlowObjects
{
private:
    SelectionManager* selectionManager = nullptr;
    UndoRedoManager* undoRedoManager = nullptr;
public:

    FlowObjects(SelectionManager* _selectionManager, UndoRedoManager* _undoredoManager);

    SelectionManager* getSelectionManager();
    UndoRedoManager* getUndoRedoManager();
};

