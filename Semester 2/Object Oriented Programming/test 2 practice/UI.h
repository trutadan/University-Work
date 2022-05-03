#pragma once
#include "Service.h"

class UI
{
public:
	UI(Service);

	void run_program();

	void add_new_building();

	void display_all_buildings();

	void display_restored_buildings();

	void save_to_file();

	void populate_buildings();

	~UI();

private:
	Service service;
};

