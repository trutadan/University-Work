#pragma once
#include "Service.h"
#include <iostream>

class UI
{
public:
	UI();

	UI(Service);

	void add_new_department();

	void display_all_departments();

	void display_efficient_departments();

	void save_to_file();

	void populate_departments();

	void run_program();

	~UI();

private:
	Service service;
};

