#pragma once
#include "Controller.h"
class UI
{
private:
	Controller controller;

public:
	UI(Controller&);

	void show_all_players() const;

	void show_players_for_given_team(const std::string&);

	void start_program();
};

