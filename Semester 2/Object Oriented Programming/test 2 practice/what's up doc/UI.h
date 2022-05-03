#pragma once
#include "Person.h"
class UI
{
public:
	UI();

	UI(Person);

	void add_new_measurement();

	void display_all_measurements();

	void is_person_healthy();

	void save_to_file();

	void populate();

	void run_program();

	~UI();

private:
	Person person;
};

