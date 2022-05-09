#pragma once
#include "../Repository/Repository.h"
#include <string>

class Validator {
public:
    static void validate_event_fields(const std::string& title, const std::string& description,
        const std::string& year, const std::string& month, const std::string& day, const std::string& hour, const std::string& minutes,
        const std::string& number_of_people, const std::string& link);

    static void validate_month(const std::string& month_string);

    static void validate_existent_event_in_repository(Repository* repository, const std::string& title);

    static void validate_nonexistent_event_in_repository(Repository* repository, const std::string& title);

    static void validate_nonexistent_event_in_list(Repository* repository, const std::string& title);
};
