#pragma once
#include "FileRepository.h"
#include "sqlite3.h"

// inspiration source: https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/
// sqlite3 database online viewer: https://inloop.github.io/sqlite-viewer/
// no additional installations; add "sqlite3.lib" to <Project->App Properties->Linker->Input->Additional Dependencies>

class SQLRepository : public FileRepository
{
public:
	SQLRepository();

	SQLRepository(const std::string& _file_name);

	void add_event(const Event& new_event) override;

	void remove_event(const std::string& title) override;

	void update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link) override;

	~SQLRepository() override;

private:
	void read_from_file() override;

	void save_to_file() override;
};
