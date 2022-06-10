#pragma once
#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>

class FileRepository : public Repository
{
public:
	FileRepository();

	FileRepository(const std::string& _file_name);

	void add_event(const Event& new_event) override;

	void remove_event(const std::string& title) override;

	void update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link) override;

	std::vector<Event>& get_all_events() override;

	int get_length() override;

	virtual ~FileRepository();

protected:
	virtual void read_from_file() = 0;

	virtual void save_to_file() = 0;
};
