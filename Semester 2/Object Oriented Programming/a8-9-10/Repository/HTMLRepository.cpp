#include "HTMLRepository.h"
#include "../Functions/Validator.h"

HTMLRepository::HTMLRepository() { {} }

HTMLRepository::HTMLRepository(const std::string& file_name)
{
	this->type = file_name;
}

void HTMLRepository::read_from_file()
{
	std::ifstream fin(this->type);
	// file is empty
	if (fin.peek() == std::ifstream::traits_type::eof()) {
		this->events.clear();
		return;
	}

	std::string line;
	std::vector<Event> new_list_of_events;

	auto strip_table_data_cell = [](std::string& line) {
		size_t start = line.find_first_of(">"),
			end = line.find_last_of("<");

		line = line.substr(start + 1, end - start - 1);
	};

	auto strip_link_from_href = [](std::string& line) {
		size_t start = line.find_first_of("\""),
			end = line.find_last_of("\"");

		line = line.substr(start + 1, end - start - 1);
	};

	bool table_header_found = false;

	while (std::getline(fin, line)) {
		strip(line);

		if (line == "<tr>" && table_header_found) {
			std::string title, description, date, time, number_of_people, link;

			std::getline(fin, title);
			strip_table_data_cell(title);

			std::getline(fin, description);
			strip_table_data_cell(description);

			std::getline(fin, date);
			strip_table_data_cell(date);

			std::getline(fin, time);
			strip_table_data_cell(time);

			std::getline(fin, number_of_people);
			strip_table_data_cell(number_of_people);

			std::getline(fin, link);
			strip_table_data_cell(link);
			strip_link_from_href(link);

			if (title.empty() || description.empty() || date.empty() || time.empty() || number_of_people.empty() || link.empty())
				throw FileError("The file does not have an appropriate format!");

			std::vector<std::string> date_split = split(date, '/');
			std::string day, month, year;

			if (date_split.size() != 3)
				throw FileError("The file does not have an appropriate format!");

			day = date_split[0], month = date_split[1], year = date_split[2];

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

		if (line == "<tr>")
			table_header_found = true;
	}
	
	this->events = new_list_of_events;
	fin.close();
}

void HTMLRepository::save_to_file()
{
	std::ofstream fout(this->type);
	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	
	// website title
	fout << "\t<head>\n";
	fout << "\t\t<title>Events</title>\n";
	fout << "\t</head>\n\n";

	// table
	fout << "\t<body>\n";
	fout << "\t\t<table border=\"1\">\n";
	
	// table header
	fout << "\t\t\t<tr>\n";
	fout << "\t\t\t\t<td>Title</td>\n";
	fout << "\t\t\t\t<td>Description</td>\n";
	fout << "\t\t\t\t<td>Date</td>\n";
	fout << "\t\t\t\t<td>Time</td>\n";
	fout << "\t\t\t\t<td>Number of people</td>\n";
	fout << "\t\t\t\t<td>Link</td>\n";
	fout << "\t\t\t</tr>\n\n";

	// each row will represent an event
	for (const Event& event : this->events) {
		fout << "\t\t\t<tr>\n";
		fout << "\t\t\t\t<td>" << event.get_title() << "</td>\n";
		fout << "\t\t\t\t<td>" << event.get_description() << "</td>\n";
		fout << "\t\t\t\t<td>" << event.get_datetime().date_to_string() << "</td>\n";
		fout << "\t\t\t\t<td>" << event.get_datetime().time_to_string() << "</td>\n";
		fout << "\t\t\t\t<td align=\"center\" valign=\"center\">" << event.get_number_of_people() << "</td>\n";
		fout << "\t\t\t\t<td><a href = \"" << event.get_link() << "\">more..</a></td>\n";
		fout << "\t\t\t</tr>\n\n";
	}

	// close tags
	fout << "\t\t</table>\n";
	fout << "\t</body>\n";
	fout << "</html>";

	fout.close();
}

HTMLRepository::~HTMLRepository() { {} }
