#pragma once
#include <string>

class Player
{
private:
	std::string name;
	std::string nationality;
	std::string team;
	int number_of_goals;

public:
	Player(const std::string&, const std::string&, const std::string&, const int&);

	const std::string& get_name() const;

	const int& get_number_of_goals() const;

	const std::string& get_team() const;

	std::string player_to_string() const;

};

