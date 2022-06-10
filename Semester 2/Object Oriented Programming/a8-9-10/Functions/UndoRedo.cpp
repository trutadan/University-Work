#include "UndoRedo.h"

UndoRedoAdd::UndoRedoAdd(const Event& _event, Repository* _repository) {
    this->added_event = _event;
    this->repository = _repository;
}

void UndoRedoAdd::undo() {
    int index = this->repository->find_event(this->added_event.get_title());
    this->repository->remove_event(added_event.get_title());
}

void UndoRedoAdd::redo() {
    this->repository->add_event(this->added_event);
}

UndoRedoRemove::UndoRedoRemove(const Event& _event, Repository* _repository) {
    this->removed_event = _event;
    this->repository = _repository;
}

void UndoRedoRemove::undo() {
    this->repository->add_event(this->removed_event);
}

void UndoRedoRemove::redo() {
    this->repository->remove_event(this->removed_event.get_title());
}

UndoRedoUpdate::UndoRedoUpdate(const Event& _old_event, const Event& _new_event, Repository* _repository) {
    this->old_event = _old_event;
    this->new_event = _new_event;
    this->repository = _repository;
}

void UndoRedoUpdate::undo() {
    this->repository->update_event(this->old_event.get_title(), this->old_event.get_description(), this->old_event.get_datetime(), this->old_event.get_number_of_people(), this->old_event.get_link());
}

void UndoRedoUpdate::redo() {
    this->repository->update_event(this->new_event.get_title(), this->new_event.get_description(), this->new_event.get_datetime(), this->new_event.get_number_of_people(), this->new_event.get_link());
}
