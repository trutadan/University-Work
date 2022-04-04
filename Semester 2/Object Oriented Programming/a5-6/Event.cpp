#include "Event.h"
#include "Validator.h"
#include "Functions.h"
#include "Exceptions.h"

Event::Event() : title(""), description(""), datetime(), number_of_people(0), link("")
{
}

Event::Event(std::string _title, std::string _description, Datetime _datetime, int _number_of_people, std::string _link)
	: title(_title), description(_description), datetime(_datetime), number_of_people(_number_of_people), link(_link)
{
}

Event::Event(const Event& copy) 
	: title(copy.title), description(copy.description), datetime(copy.datetime), number_of_people(copy.number_of_people), link(copy.link)
{
}

std::string Event::get_title() const
{
	return title;
}

std::string Event::get_description() const
{
	return description;
}

Datetime Event::get_datetime() const
{
	return datetime;
}

int Event::get_number_of_people() const
{
	return number_of_people;
}

std::string Event::get_link() const
{
	return link;
}

void Event::set_description(std::string new_description)
{
	description = new_description;
}

void Event::set_datetime(Datetime new_datetime)
{
	datetime = new_datetime;
}

void Event::set_number_of_people(int new_number_of_people)
{
	number_of_people = new_number_of_people;
}

void Event::set_link(std::string new_link)
{
	link = new_link;
}

bool Event::operator==(const Event& other) const
{
    return title == other.title;
}

void Event::open() const
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->get_link().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::istream& operator>>(std::istream& reader, Event& event)
{
    std::string line;
    std::getline(reader, line);

    if (line.empty())
        return reader;

    strip(line);
    std::stringstream stream(line);

    std::string title;
    std::string description;
    std::string date;
    std::string time;
    std::string number_of_people;
    std::string link;

    std::getline(stream, title, ',');
    strip(title);

    std::getline(stream, description, ',');
    strip(description);

    std::getline(stream, date, ',');
    strip(date);

    std::getline(stream, time, ',');
    strip(time);

    std::getline(stream, number_of_people, ',');
    strip(number_of_people);

    std::getline(stream, link, ',');
    strip(link);

    if (title.empty() || description.empty() || date.empty() || time.empty() || number_of_people.empty() || link.empty())
        throw ValueError("Not enough arguments.");

    std::vector<std::string> date_split = split(date, '/');
    std::string day, month, year;

    if (date_split.size() != 3)
        throw ValueError("Wrong date format.");

    day = date_split[0], month = date_split[1], year = date_split[2];

    std::vector<std::string> time_split = split(time, ':');
    std::string hour, minutes;

    if (time_split.size() != 2)
        throw ValueError("Wrong time format.");

    hour = time_split[0], minutes = time_split[1];

    Validator::validate_event_fields(title, description, year, month, day, hour, minutes, number_of_people, link);

    int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
    int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

    Datetime datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

    int number_of_people_integer = std::stoi(number_of_people);

    event = Event(title, description, datetime, number_of_people_integer, link);

    return reader;
}
