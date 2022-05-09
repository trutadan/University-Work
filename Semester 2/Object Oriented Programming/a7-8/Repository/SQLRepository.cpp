#include "SQLRepository.h"
#include "../Functions/Validator.h"

void create_database(const std::string& file_name)
{
    sqlite3* database;
    char* error_message;

    int exit_code = sqlite3_open(file_name.c_str(), &database);
    if (exit_code)
        throw FileError("Error opening the database.");

    std::string command = "CREATE TABLE IF NOT EXISTS events (title VARCHAR(100) PRIMARY KEY,"
        "description VARCHAR(100),"
        "date VARCHAR(100),"
        "time VARCHAR(100),"
        "number_of_people INTEGER,"
        "link VARCHAR(100)"
        ");";

    exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);
    if (exit_code != SQLITE_OK)
        throw FileError("Error executing command inside the database.");

    sqlite3_close(database);
}

SQLRepository::SQLRepository() { {} }

SQLRepository::SQLRepository(const std::string& file_name)
{
	this->type = file_name;
    create_database(file_name);
}

int get_event_from_database(void* list, int count, char** data, char** columns)
{
    auto* list_of_events = (std::vector<Event> *)list;
    std::string strings[6];

    for (int i = 0; i < 6; ++i)
        strings[i] = std::string(data[i]);

    std::string date = strings[2], time = strings[3];
    std::vector<std::string> date_split = split(date, '/');
    std::string day, month, year;

    if (date_split.size() != 3)
        throw ValueError("Wrong date format.");

    day = date_split[2], month = date_split[1], year = date_split[0];

    std::vector<std::string> time_split = split(time, ':');
    std::string hour, minutes;

    if (time_split.size() != 2)
        throw ValueError("Wrong time format.");

    hour = time_split[0], minutes = time_split[1];

    Validator::validate_event_fields(strings[0], strings[1], year, month, day, hour, minutes, strings[4], strings[5]);

    int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
    int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

    Datetime datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

    list_of_events->push_back(Event(strings[0], strings[1], datetime, std::stoi(strings[4]), strings[5]));

    return 0;
}

void SQLRepository::add_event(const Event& new_event)
{
    Repository::add_event(new_event);

    sqlite3* database;
    char* error_message;
    int exit_code = sqlite3_open(this->type.c_str(), &database);

    if (exit_code)
        throw FileError("Error opening the database.");

    std::string command = "INSERT INTO events VALUES ('";
    command += new_event.get_title() + "','";
    command += new_event.get_description() + "','";
    command += new_event.get_datetime().date_to_string() + "','";
    command += new_event.get_datetime().time_to_string() + "',";
    command += std::to_string(new_event.get_number_of_people()) + ",'";
    command += new_event.get_link() + "');";

    exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);
    if (exit_code != SQLITE_OK)
        throw FileError("Error executing command inside the database!");

    sqlite3_close(database);
}

void SQLRepository::remove_event(const std::string& title)
{
    Repository::remove_event(title);

    sqlite3* database;
    char* error_message;
    int exit_code = sqlite3_open(this->type.c_str(), &database);

    if (exit_code)
        throw FileError("Error opening the database.");

    std::string command = "DELETE FROM events WHERE title='";
    command += title + "';";

    exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);
    if (exit_code != SQLITE_OK)
        throw FileError("Error executing command inside the database.");

    sqlite3_close(database);
}

void SQLRepository::update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link)
{
    Repository::update_event(title, new_description, new_datetime, new_number_of_people, new_link);
    
    sqlite3* database;
    char* error_message;
    int exit_code = sqlite3_open(this->type.c_str(), &database);

    if (exit_code)
        throw RepositoryError("Error opening the database.");

    std::string command = "UPDATE events SET ";
    command = command + "description='" + new_description + "',";
    command = command + "date='" + new_datetime.date_to_string() + "',";
    command = command + "time='" + new_datetime.time_to_string() + "',";
    command = command + "number_of_people=" + std::to_string(new_number_of_people) + ",";
    command = command + "link='" + new_link + "' WHERE title='" + title + "';";

    exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);
    if (exit_code != SQLITE_OK)
        throw RepositoryError("Error executing command inside the database.");

    sqlite3_close(database);
}

void SQLRepository::read_from_file()
{
    sqlite3* database;
    char* error_message;
    int exit_code = sqlite3_open(this->type.c_str(), &database);

    if (exit_code)
        throw FileError("Error opening the database.");

    std::string command = "SELECT * FROM events;";
    std::vector<Event> new_list_of_events;

    exit_code = sqlite3_exec(database, command.c_str(), get_event_from_database, &new_list_of_events, &error_message);
    if (exit_code != SQLITE_OK)
        throw FileError("Error executing command inside the database.");

    sqlite3_close(database);
    this->events = new_list_of_events;
}

void SQLRepository::save_to_file()
{
    sqlite3* database;
    char* error_message;

    int exit_code = sqlite3_open(this->type.c_str(), &database);
    if (exit_code)
        throw FileError("Error opening the database.");

    std::string command = "DELETE FROM events;";
    exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);
    if (exit_code != SQLITE_OK)
        throw FileError("Error executing command inside the database.");

    for (const auto& event : this->events) {
        command = "INSERT INTO turrets VALUES ('";
        command += event.get_title() + "','";
        command += event.get_description() + "','";
        command += event.get_datetime().date_to_string() + "','";
        command += event.get_datetime().time_to_string() + "',";
        command += std::to_string(event.get_number_of_people()) + ",'";
        command += event.get_link() + "');";

        exit_code = sqlite3_exec(database, command.c_str(), nullptr, nullptr, &error_message);

        if (exit_code != SQLITE_OK)
            throw FileError("Error executing command inside the database.");
    }

    sqlite3_close(database);
}

SQLRepository::~SQLRepository() { {} }
