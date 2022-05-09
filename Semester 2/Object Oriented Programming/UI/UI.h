#pragma once
#include "../Controller/Controller.h"
#include "../Functions/Functions.h"

class UI
{
public:
	UI(Controller& _controller);

	void start_program();

	~UI() = default;

private:
	Controller& controller;

	void display_all_events_from_repository();

	void display_all_events_from_list();
	
	void ask_admin_for_new_file();

	void ask_user_for_new_file();
};