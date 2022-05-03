#include "Player.h"

Player::Player(const std::string& _name, const std::string& _nationality, const std::string& _team, const int& _number_of_goals) : name(_name), nationality(_nationality), team(_team), number_of_goals(_number_of_goals)
{
}

const std::string& Player::get_name() const
{
	return this->name;
}

const int& Player::get_number_of_goals() const
{
	return this->number_of_goals;
}

const std::string& Player::get_team() const
{
	return this->team;
}

std::string Player::player_to_string() const
{
	std::string player_string;
	player_string = this->name + " | " + this->nationality + " | " + this->team + " | " + std::to_string(this->number_of_goals);

	return player_string;
}
