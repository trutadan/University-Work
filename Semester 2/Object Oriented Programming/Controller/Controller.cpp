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
