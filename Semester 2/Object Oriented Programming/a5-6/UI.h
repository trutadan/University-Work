#pragma once
#include "Controller.h"
#include "Functions.h"

class UI
{
public:
	UI(Controller* _controller);

	void start_program();

	void display_all_events_from_repository();

	void display_all_events_from_list();

	void display_all_events_from_removal_history();

private:
	Controller* controller;
};