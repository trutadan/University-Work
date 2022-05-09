#include "Repository.h"
#include "../Functions/Validator.h"

Repository::Repository() 
{
    this->type = "inmemory";
}

bool Repository::has_event(const std::string& title)
{
    for (const Event& each_event : this->events)
        if (strcasecmp(each_event.get_title(), title))
            return true;

    return false;
}

int Repository::find_event(const std::string& title)
{
    Validator::validate_nonexistent_event_in_repository(this, title);
    
    int index = 0;

    for (const Event& each_event : this->events)
        if (strcasecmp(each_event.get_title(), title))
            return index;
        else index++;
}

void Repository::add_event(const Event& new_event)
{
    Validator::validate_existent_event_in_repository(this, new_event.get_title());
    this->events.push_back(new_event);
}

void Repository::remove_event(const std::string& title)
{
    int index = find_event(title);
    this->events.erase(this->events.begin() + index);
}

void Repository::update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link)
{
    Event updated_event{ title, new_description, new_datetime, new_number_of_people, new_link };
    this->events[find_event(title)] = updated_event;
}

std::vector<Event>& Repository::get_all_events()
{
    return this->events;
}

int Repository::get_length()
{
    return this->events.size();
}

std::string Repository::get_type() const
{
    return this->type;
}

void Repository::set_type(std::string new_type)
{
    this->type = new_type;
}

Repository::~Repository() { {} }
