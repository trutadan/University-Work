#include "TextFileRepository.h"
#include "../Functions/Validator.h"

TextFileRepository::TextFileRepository() { {} }

TextFileRepository::TextFileRepository(const std::string& file_name)
{
	this->type = file_name;
}

void TextFileRepository::read_from_file()
{
	std::ifstream fin(this->type);
	// file is empty
	if (fin.peek() == std::ifstream::traits_type::eof()){
		this->events.clear();
		return;
	}

    std::string line;
	std::vector<Event> new_list_of_events;

	while (std::getline(fin, line)) {
		strip(line);
		std::stringstream parser(line);
		Event event;
		
		try {
			parser >> event;
		}

		catch (ValueError&){
			throw FileError("The file does not have an appropriate format!");
		}
		
		new_list_of_events.push_back(event);
	}

	this->events = new_list_of_events;
	fin.close();
}

void TextFileRepository::save_to_file()
{
	std::ofstream fout(this->type);

	for (const auto& turret : this->events)
		fout << turret << '\n';
	
	fout.close();
}

TextFileRepository::~TextFileRepository() { {} }