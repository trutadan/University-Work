#include "Controller.h"
#include <algorithm>

Controller::Controller(Repository& _repository) : repository(_repository)
{
}

bool Controller::add_player(const Player& new_player)
{
	/*
	Add new player to the repository if the name of the player does not belong to any of the existent players.
	Return: true if the player has been added, false if not.
	*/

    return this->repository.add_to_repository(new_player);
}

std::vector<Player> Controller::get_players() const
{
    return this->repository.get_players_from_repository();
}

std::vector<Player> Controller::get_sorted_players_by_number_of_goals() const
{
	/*
	Get the list of players from the repository and sort them by the number of goals.
	Return: a vector containing the players sorted by the number of goals.
	*/

	std::vector<Player> players = this->repository.get_players_from_repository();

	auto sort_method = [](const Player& first_player, const Player& second_player) {
		return first_player.get_number_of_goals() < second_player.get_number_of_goals();
	};

	std::sort(players.begin(), players.end(), sort_method);

	return players;
}
