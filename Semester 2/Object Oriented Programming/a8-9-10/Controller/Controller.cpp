#include "Controller.h"
#include "../Functions/Exceptions.h"

Controller::Controller(Repository* _repository, Repository* _list) : repository(_repository), list(_list)
{
}

std::vector<Event> Controller::get_all_events_from_repository()
{
    return this->repository->get_all_events();
}

int Controller::get_repository_length() const
{
    return this->repository->get_length();
}

void Controller::add_event_to_repository(const std::string& title, const std::string& description, const Datetime& datetime, const int& number_of_people, const std::string& link)
{
    Event event{ title, description, datetime, number_of_people, link };
    this->repository->add_event(event);

    std::shared_ptr<UndoRedoAction> add_action = std::make_shared<UndoRedoAdd>(event, this->repository);
    this->admin_undo_stack.push_back(add_action);
    this->admin_redo_stack.clear();
}

void Controller::remove_event_from_repository(const std::string& title)
{
    int index = this->repository->find_event(title);
    Event event = this->repository->get_all_events()[index];

    this->repository->remove_event(title);

    try {
        if (is_event_from_repository_in_list(title))
            this->list->remove_event(title);
    }

    catch (ListError&) {

    }

    std::shared_ptr<UndoRedoAction> remove_action = std::make_shared<UndoRedoRemove>(event, this->repository);
    this->admin_undo_stack.push_back(remove_action);
    this->admin_redo_stack.clear();
}

void Controller::update_event_from_repository(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link)
{
    this->repository->update_event(title, new_description, new_datetime, new_number_of_people, new_link);

    try {
        if (is_event_from_repository_in_list(title))
            this->list->update_event(title, new_description, new_datetime, new_number_of_people, new_link);
    }

    catch (ListError&) {

    }

    Event old_event = this->repository->get_all_events()[this->repository->find_event(title)];
    Event new_event(title, new_description, new_datetime, new_number_of_people, new_link);

    std::shared_ptr<UndoRedoAction> update_action = std::make_shared<UndoRedoUpdate>(old_event, new_event, this->repository);
    this->admin_undo_stack.push_back(update_action);
    this->admin_redo_stack.clear();
}

std::vector<Event> Controller::get_all_events_from_list()
{
    return this->list->get_all_events();
}

int Controller::get_list_length() const
{
    return this->list->get_length();
}

void Controller::add_event_to_list(const Event& new_event)
{
    int event_index = this->repository->find_event(new_event.get_title());
    Event repository_event = this->repository->get_all_events()[event_index];
    repository_event.set_number_of_people(repository_event.get_number_of_people() + 1);
    this->update_event_from_repository(repository_event.get_title(), repository_event.get_description(), repository_event.get_datetime(), repository_event.get_number_of_people(), repository_event.get_link());

    this->list->add_event(repository_event);

    std::shared_ptr<UndoRedoAction> add_action = std::make_shared<UndoRedoAdd>(repository_event, this->list);
    this->user_undo_stack.push_back(add_action);
    this->user_redo_stack.clear();
}

void Controller::remove_event_from_list(const std::string& title)
{
    this->list->remove_event(title);

    int event_index = this->repository->find_event(title);
    Event repository_event = this->repository->get_all_events()[event_index];
    this->update_event_from_repository(title, repository_event.get_description(), repository_event.get_datetime(), repository_event.get_number_of_people() - 1, repository_event.get_link());
}

bool Controller::is_event_from_repository_in_list(const std::string& title)
{
    return this->list->has_event(title);
}

std::vector<Event> Controller::get_all_unadded_events_for_given_month(const int& month)
{
    std::vector<Event> filtered_events;
    std::vector<Event> events = this->get_all_events_from_repository();

    std::copy_if(events.begin(), events.end(), std::back_inserter(filtered_events), [this, &month](Event& _event) {
        return (month == _event.get_datetime().get_month()) && (!this->is_event_from_repository_in_list(_event.get_title())); });
        
    return filtered_events;
}

std::vector<Event> Controller::get_all_unadded_events()
{
    std::vector<Event> filtered_events;
    std::vector<Event> events = this->get_all_events_from_repository();

    std::copy_if(events.begin(), events.end(), std::back_inserter(filtered_events), [this](Event& _event) {
        return !this->is_event_from_repository_in_list(_event.get_title()); });

    return filtered_events;
}

void Controller::sort_events_by_date(std::vector<Event>& events_list)
{
    std::sort(events_list.begin(), events_list.end(), check_sooner_event);
}

void Controller::change_admin_repository_type(const std::string& repository_type)
{
    if (repository_type == "inmemory") {
        auto new_repository = new Repository;
        this->repository = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".txt") {
        auto new_repository = new TextFileRepository{ repository_type };
        this->repository = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".csv") {
        auto new_repository = new CSVRepository{ repository_type };
        this->repository = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 5) == ".html") {
        auto new_repository = new HTMLRepository{ repository_type };
        this->repository = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".sql") {
        auto new_repository = new SQLRepository{ repository_type };
        this->repository = new_repository;
    }

    else
        throw FileError("The type is invalid!");
}

void Controller::change_user_repository_type(const std::string& repository_type)
{
    if (repository_type == "inmemory") {
        auto new_repository = new Repository;
        this->list = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".txt") {
        auto new_repository = new TextFileRepository{ repository_type };
        this->list = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".csv") {
        auto new_repository = new CSVRepository{ repository_type };
        this->list = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 5) == ".html") {
        auto new_repository = new HTMLRepository{ repository_type };
        this->list = new_repository;
    }

    else if (repository_type.substr(repository_type.size() - 4) == ".sql") {
        auto new_repository = new SQLRepository{ repository_type };
        this->list = new_repository;
    }

    else
        throw FileError("The type is invalid!");
}

int Controller::get_number_of_people_by_event_name(const std::string& event_name) {
    int position = this->repository->find_event(event_name);

    return this->get_all_events_from_repository()[position].get_number_of_people();
}

std::vector<std::string> Controller::get_all_event_names_from_repository() {
    std::vector<std::string> names;

    for (const Event& event : this->get_all_events_from_repository())
        names.push_back(event.get_title());

    return names;
}

std::string Controller::get_repository_type() const
{
    return this->repository->get_type();
}

std::string Controller::get_list_type() const
{
    return this->list->get_type();
}

void open_file(const std::string& file_type)
{
    std::string command;

    command = "start " + file_type;

    system(command.c_str());
}

void Controller::open_repository_file()
{
    std::string repository_type = this->get_repository_type();
    open_file(repository_type);
}

void Controller::open_list_file()
{
    std::string list_type = this->get_list_type();
    open_file(list_type);
}

void Controller::undo_admin_last_action()
{
    if (this->admin_undo_stack.empty())
        throw RepositoryError("No more undos left!");

    this->admin_undo_stack.back()->undo();
    this->admin_redo_stack.push_back(this->admin_undo_stack.back());
    this->admin_undo_stack.pop_back();
}

void Controller::redo_admin_last_action()
{
    if (this->admin_redo_stack.empty())
        throw RepositoryError("No more redos left!");

    this->admin_redo_stack.back()->redo();
    this->admin_undo_stack.push_back(this->admin_redo_stack.back());
    this->admin_redo_stack.pop_back();
}

void Controller::clear_admin_undo_redo_stack()
{
    this->admin_undo_stack.clear();
    this->admin_redo_stack.clear();
}

void Controller::undo_user_last_action()
{
    if (this->user_undo_stack.empty())
        throw RepositoryError("No more undos left!");

    this->user_undo_stack.back()->undo();
    this->user_redo_stack.push_back(this->user_undo_stack.back());
    this->user_undo_stack.pop_back();
}

void Controller::redo_user_last_action()
{
    if (this->user_redo_stack.empty())
        throw RepositoryError("No more redos left!");

    this->user_redo_stack.back()->redo();
    this->user_undo_stack.push_back(this->user_redo_stack.back());
    this->user_redo_stack.pop_back();
}

void Controller::clear_user_undo_redo_stack()
{
    this->user_undo_stack.clear();
    this->user_redo_stack.clear();
}
