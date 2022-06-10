#pragma once
#pragma once
#include "../Repository/Repository.h"

class UndoRedoAction {
public:
    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual ~UndoRedoAction() = default;
};

class UndoRedoAdd : public UndoRedoAction {
private:
    Event added_event;
    Repository* repository;

public:
    UndoRedoAdd(const Event& _event, Repository* _repository);

    void undo() override;

    void redo() override;

    ~UndoRedoAdd() override = default;
};

class UndoRedoRemove : public UndoRedoAction {
private:
    Event removed_event;
    Repository* repository;

public:
    UndoRedoRemove(const Event& _event, Repository* _repository);

    void undo() override;

    void redo() override;

    ~UndoRedoRemove() override = default;
};

class UndoRedoUpdate : public UndoRedoAction {
private:
    Event old_event;
    Event new_event;
    Repository* repository;

public:
    UndoRedoUpdate(const Event& _old_event, const Event& _new_event, Repository* _repository);

    void undo() override;

    void redo() override;

    ~UndoRedoUpdate() override = default;
};
