#include "Repository.h"

bool Repository::add_to_repository(const Player& new_player)
{
	for (Player player : this->players)
		if (player.get_name() == new_player.get_name())
			return false;

	this->players.push_back(new_player);
	return true;
}

std::vector<Player> Repository::get_players_from_repository() const
{
	return this->players;
}
