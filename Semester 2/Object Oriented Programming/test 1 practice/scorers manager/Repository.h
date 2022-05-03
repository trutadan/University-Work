#pragma once
#include <vector>
#include "Player.h"

class Repository
{
private:
	std::vector<Player> players;

public:
	bool add_to_repository(const Player&);

	std::vector<Player> get_players_from_repository() const;

};

