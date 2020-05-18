#include "flowobjects.h"


FlowObjects::FlowObjects(SelectionManager *_selectionManager, UndoRedoManager* _undoredoManager)
{
    if(_selectionManager == nullptr)
    {
        qFatal("[fatal][FlowContext] _selectionManager == nullptr");
    }
    if(_undoredoManager == nullptr)
    {
        qFatal("[fatal][FlowContext] _undoredoManager == nullptr");
    }
    selectionManager = _selectionManager;
    undoRedoManager = _undoredoManager;
}

SelectionManager *FlowObjects::getSelectionManager()
{
    return selectionManager;
}

UndoRedoManager *FlowObjects::getUndoRedoManager()
{
    return undoRedoManager;
}

