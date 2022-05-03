#pragma once
#include "Repository.h"

class Controller
{
private:
	Repository repository;

public:
	Controller(Repository&);

	bool add_player(const Player& new_player);

	std::vector<Player> get_players() const;

	std::vector<Player> get_sorted_players_by_number_of_goals() const;
};