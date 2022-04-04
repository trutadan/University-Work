#include "Repository.h"
#include "Validator.h"
#include "Functions.h"

Repository::Repository(DynamicVector<Event>* _events)
{
    this->events = _events;
}

bool Repository::has_event(const std::string& title)
{
    for (int index = 0; index < this->get_length(); index++) {
        Event each_event = this->events->get_elements()[index];
        if (strcasecmp(each_event.get_title(), title))
            return true;
    }

    return false;
}

int Repository::find_event(const std::string& title)
{
    Validator::validate_nonexistent_event_in_repository(this, title);

    for (int index = 0; index < this->get_length(); index++) {
        Event each_event = this->events->get_elements()[index];
        if (strcasecmp(each_event.get_title(), title))
            return index;
    }

    return -1;
}

void Repository::add_event(const Event& new_event)
{
    Validator::validate_existent_event_in_repository(this, new_event.get_title());
    this->events->add(new_event);
}

void Repository::remove_event(const std::string& title)
{
    this->events->remove(find_event(title));
}

void Repository::update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link)
{
    Event updated_event{ title, new_description, new_datetime, new_number_of_people, new_link };

    this->events->update(find_event(title), updated_event);
}

int Repository::get_length() const
{
    return this->events->get_length();
}

void Repository::add_event_without_validation(const Event& new_event)
{
    this->events->add(new_event);
}

Event* Repository::get_all_events()
{
    return (Event*)this->events->get_elements();
}