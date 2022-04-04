#pragma once
#include <string>
#include "Repository.h"

class Validator {
public:
    static void validate_event_fields(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, 
        const std::string&, const std::string&, const std::string&, const std::string&);

    static void validate_month(const std::string&);

    static void validate_existent_event_in_repository(Repository*, const std::string&);

    static void validate_nonexistent_event_in_repository(Repository*, const std::string&);

    static void validate_nonexistent_event_in_list(Repository*, const std::string&);
};
