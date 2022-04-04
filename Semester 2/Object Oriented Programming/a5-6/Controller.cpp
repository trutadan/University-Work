#include "Controller.h"
#include "Exceptions.h"

Controller::Controller(Repository* _repository, Repository* _list, Repository* _removal_history) : repository(_repository), list(_list), removal_history(_removal_history)
{
}

Event* Controller::get_all_events_from_repository()
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
    this->removal_history->add_event_without_validation(event);

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

Event* Controller::get_all_events_from_list()
{
    return this->list->get_all_events();
}

int Controller::get_list_length() const
{
    return this->list->get_length();
}

void Controller::add_event_to_list(const Event& event)
{
    int event_index = this->repository->find_event(event.get_title());
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

DynamicVector<Event>* Controller::get_all_unadded_events_for_given_month(const int month)
{
    DynamicVector<Event>* filtered_events = new DynamicVector<Event>;

    for (int index = 0; index < this->get_repository_length(); index++) {
        Event event = this->get_all_events_from_repository()[index];

        if (month == event.get_datetime().get_month())
            if (!this->is_event_from_repository_in_list(event.get_title()))
                filtered_events->add(event);
    }

    return filtered_events;
}

DynamicVector<Event>* Controller::get_all_unadded_events()
{
    DynamicVector<Event>* filtered_events = new DynamicVector<Event>;

    for (int index = 0; index < this->get_repository_length(); index++) {
        Event event = this->get_all_events_from_repository()[index];
    
        if (!this->is_event_from_repository_in_list(event.get_title()))
            filtered_events->add(event);
    }

    return filtered_events;
}

void Controller::sort_events_by_date(Event* events_list, const int& length)
{
    int is_list_sorted = 0;

    while (!is_list_sorted) {
        is_list_sorted = 1;

        for (int index = 0; index < length - 1; index++)
            if (!check_sooner_event(events_list[index], events_list[index + 1])) {
                is_list_sorted = 0;

                Event auxiliary_event = events_list[index];
                events_list[index] = events_list[index + 1];
                events_list[index + 1] = auxiliary_event;
            }
    }
}

Event* Controller::get_removed_events_from_repository()
{
    return this->removal_history->get_all_events();
}

int Controller::get_removal_history_length() const
{
    return this->removal_history->get_length();
}
