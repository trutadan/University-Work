#include "FileRepository.h"
#include "../Functions/Validator.h"

FileRepository::FileRepository() { {} }

FileRepository::FileRepository(const std::string& file_name)
{
	this->type = file_name;
}

void FileRepository::add_event(const Event& event)
{
	this->read_from_file();
	Repository::add_event(event);
	this->save_to_file();
}

void FileRepository::remove_event(const std::string& title)
{
	this->read_from_file();
	Repository::remove_event(title);
	this->save_to_file();
}

void FileRepository::update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link)
{
	this->read_from_file();
	Repository::update_event(title, new_description, new_datetime, new_number_of_people, new_link);
	this->save_to_file();
}

std::vector<Event>& FileRepository::get_all_events()
{
	this->read_from_file();
	return Repository::get_all_events();
}

int FileRepository::get_length()
{
	this->read_from_file();
	return Repository::get_length();
}

FileRepository::~FileRepository() { {} }
