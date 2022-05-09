#include "Validator.h"
#include "Exceptions.h"
#include <regex>
#include <iostream>

const int MINIMUM_VALID_YEAR = 2022;

void Validator::validate_event_fields(const std::string& title, const std::string& description,
    const std::string& year, const std::string& month, const std::string& day, const std::string& hour, const std::string& minutes,
    const std::string& number_of_people, const std::string& link)
{
    if (title.empty() || description.empty() || link.empty())
        throw ValueError("Cannot have empty fields.");

    for (auto character : day)
        if (character > '9' || character < '0')
            throw ValueError("The number of people must be a positive integer.");

    for (auto character : month)
        if (character > '9' || character < '0')
            throw ValueError("The number of people must be a positive integer.");

    for (auto character : year)
        if (character > '9' || character < '0')
            throw ValueError("The number of people must be a positive integer.");

    for (auto character : number_of_people)
        if (character > '9' || character < '0')
            throw ValueError("The number of people must be a positive integer.");

    std::string url_pattern = "(https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|www\.[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9]+\.[^\s]{2,}|www\.[a-zA-Z0-9]+\.[^\s]{2,})";
    std::regex link_regex(url_pattern);
    if (!std::regex_match(link, link_regex))
        throw ValueError("The link doesn't seem to have an appropriate form.");

    std::string time = hour + ":" + minutes;
    const std::regex time_pattern("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    if (!std::regex_match(time, time_pattern))
        throw ValueError("The time format provided is not valid.");

    int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
    
    if (year_integer < MINIMUM_VALID_YEAR)
        throw ValueError("You can only add events in the current year.");

    if (month_integer < 1 || month_integer > 12)
        throw ValueError("The month's value must be between 1 and 12.");

    if (day_integer < 1 || day_integer > 31)
        throw ValueError("The day value must be between 1 and 31.");

    if (month_integer == 2) {
        if (((year_integer % 4 == 0) && (year_integer % 100 != 0)) || (year_integer % 400 == 0)) {
            if (day_integer > 29)
                throw ValueError("In a leap year, February has only 29 days.");
        }
        else {
            if (day_integer > 28)
                throw ValueError("In a non-leap year, February has only 28 days.");
        }
    }

    if (month_integer == 4 && day_integer > 30)
        throw ValueError("April has only 30 days.");

    if (month_integer == 6 && day_integer > 30)
        throw ValueError("June has only 30 days.");

    if (month_integer == 9 && day_integer > 30)
        throw ValueError("September has only 30 days.");

    if (month_integer == 11 && day_integer > 30)
        throw ValueError("November has only 30 days.");
}

bool is_number(const std::string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

void Validator::validate_month(const std::string& month)
{
    if (!is_number(month))
        throw ValueError("You need an integer for the month.");

    int month_integer = std::stoi(month);
    if (month_integer < 1 || month_integer > 12)
        throw ValueError("That's not a valid month number.");
}

void Validator::validate_existent_event_in_repository(Repository* repository, const std::string& title)
{
    if (repository->has_event(title))
        throw RepositoryError("An event with the given title already exists.");
}

void Validator::validate_nonexistent_event_in_repository(Repository* repository, const std::string& title)
{
    if (!repository->has_event(title))
        throw RepositoryError("There is no event with the given title.");
}

void Validator::validate_nonexistent_event_in_list(Repository* list, const std::string& title)
{
    if (!list->has_event(title))
        throw ListError("There is no event with the given title.");
}
