#include "Functions.h"

void strip(std::string& string) {
    while (!string.empty() && (string.back() == ' ' || string.back() == '\t' || string.back() == '\n'))
        string.pop_back();

    reverse(string.begin(), string.end());

    while (!string.empty() && (string.back() == ' ' || string.back() == '\t' || string.back() == '\n'))
        string.pop_back();

    reverse(string.begin(), string.end());
}

std::vector<std::string> split(const std::string& string, char delimitator) {
    std::vector<std::string> result;
    std::stringstream string_stream(string);
    std::string item;

    while (getline(string_stream, item, delimitator))
        result.push_back(item);

    return result;
}

bool strcasecmp(const std::string& first_string, const std::string& second_string){
    unsigned int size_of_first_string = first_string.size();

    if (second_string.size() != size_of_first_string)
        return false;

    for (unsigned int index = 0; index < size_of_first_string; index++)
        if (tolower(first_string[index]) != tolower(second_string[index]))
            return false;

    return true;
}

bool check_sooner_event(const Event& first_event, const Event& second_event)
{
    if (first_event.get_datetime().get_year() > second_event.get_datetime().get_year())
        return false;

    else if (first_event.get_datetime().get_year() < second_event.get_datetime().get_year())
        return true;

    else {
        if (first_event.get_datetime().get_month() > second_event.get_datetime().get_month())
            return false;

        else if (first_event.get_datetime().get_month() < second_event.get_datetime().get_month())
            return true;

        else {
            if (first_event.get_datetime().get_day() > second_event.get_datetime().get_day())
                return false;

            else if (first_event.get_datetime().get_day() < second_event.get_datetime().get_day())
                return true;
        
            else {
                if (first_event.get_datetime().get_hour() > second_event.get_datetime().get_hour())
                    return false;

                else if (first_event.get_datetime().get_hour() < second_event.get_datetime().get_hour())
                    return true;

                else {
                    if (first_event.get_datetime().get_minutes() > second_event.get_datetime().get_minutes())
                        return false;

                    else if (first_event.get_datetime().get_minutes() > second_event.get_datetime().get_minutes())
                        return true;
                }
            }
        }
    }

    return true;
}
