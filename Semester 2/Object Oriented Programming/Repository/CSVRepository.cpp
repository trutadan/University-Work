#include "../Functions/Validator.h"
#include "CSVRepository.h"

CSVRepository::CSVRepository() { {} }

CSVRepository::CSVRepository(const std::string& file_name)
{
	this->type = file_name;
}

void CSVRepository::read_from_file()
{
	std::ifstream fin(this->type);
	// file is empty
	if (fin.peek() == std::ifstream::traits_type::eof()) {
		this->events.clear();
		return;
	}

	std::string line;
	std::vector<Event> new_list_of_events;

	while (std::getline(fin, line)) {
		strip(line);

		std::string title, description, date, time, number_of_people, link;
		std::vector<std::string> arguments;

		arguments = split(line, ',');

		if (arguments.size() != 6)
			throw FileError("The file does not have an appropriate format!");

		title = arguments[0];
		description = arguments[1];
		date = arguments[2];
		time = arguments[3];
		number_of_people = arguments[4];
		link = arguments[5];

		if (title.empty() || description.empty() || date.empty() || time.empty() || number_of_people.empty() || link.empty())
			throw FileError("The file does not have an appropriate format!");

		std::vector<std::string> date_split = split(date, '/');
		std::string day, month, year;

		if (date_split.size() != 3)
			throw FileError("The file does not have an appropriate format!");

		day = date_split[2], month = date_split[1], year = date_split[0];

		std::vector<std::string> time_split = split(time, ':');
		std::string hour, minutes;

		if (time_split.size() != 2)
			throw FileError("The file does not have an appropriate format!");

		hour = time_split[0], minutes = time_split[1];

		try {
			Validator::validate_event_fields(title, description, year, month, day, hour, minutes, number_of_people, link);
		}

		catch (ValueError&) {
			throw FileError("The file does not have an appropriate format!");
		}

		int day_integer = std::stoi(day), month_integer = std::stoi(month), year_integer = std::stoi(year);
		int hour_integer = std::stoi(hour), minutes_integer = std::stoi(minutes);

		Datetime datetime = Datetime(year_integer, month_integer, day_integer, hour_integer, minutes_integer);

		int number_of_people_integer = std::stoi(number_of_people);

		Event event = Event(title, description, datetime, number_of_people_integer, link);

		new_list_of_events.push_back(event);
	}

	this->events = new_list_of_events;
	fin.close();
}

void CSVRepository::save_to_file()
{
    std::ofstream fout(this->type);

    for (const auto& event : events)
        fout << event.get_title() << "," << event.get_description() << "," << event.get_datetime().date_to_string() << "," << event.get_datetime().time_to_string() << "," << event.get_number_of_people() << "," << event.get_link() << std::endl;

    fout.close();
}

CSVRepository::~CSVRepository() { {} }
