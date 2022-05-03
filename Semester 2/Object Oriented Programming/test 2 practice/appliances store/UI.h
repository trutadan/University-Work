#pragma once
#include <iostream>
#include "Service.h"

class UI
{
public:
	UI();

	UI(Service);

	void add_new_appliance();

	void display_all_appliances();

	void display_all_efficient_appliances();

	void save_to_file();

	void populate_appliances();

	void run_program();

	~UI();

private:
	Service service;
};

